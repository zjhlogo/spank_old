/*!
 * \file Texture_Impl.cpp
 * \date 7-22-2011 10:49:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Texture_Impl.h"
#include <IFileMgr.h>
#include <lpng154/png.h>

static void pngReaderCallback(png_structp pPngStruct, png_bytep pData, png_size_t nSize)
{
	StreamReader* pStream = (StreamReader*)png_get_io_ptr(pPngStruct);

	if (!pStream->Read(pData, nSize))
	{
		png_error(pPngStruct,"pngReaderCallback failed");
	}
}

Texture_Impl::Texture_Impl(const char* pszFileName)
{
	m_nWidth = 0;
	m_nHeight = 0;
	m_pTextureDataRGBA = NULL;
	m_nGLTextureID = 0;

	LoadTextureFromFile(pszFileName);
	CreateGLTexture();
}

Texture_Impl::~Texture_Impl()
{
	FreeGLTexture();
	FreeTextureData();
}

uint Texture_Impl::GetWidth() const
{
	return m_nWidth;
}

uint Texture_Impl::GetHeight() const
{
	return m_nHeight;
}

bool Texture_Impl::LoadTextureFromFile(const char* pszFileName)
{
	FreeTextureData();

	StreamReader* pTextureStream = IFileMgr::GetInstance().LoadFile(pszFileName);
	if (!pTextureStream) return false;

	png_structp pPngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!pPngStruct)
	{
		png_destroy_read_struct(&pPngStruct, NULL, NULL);
		// TODO: logout
		SAFE_DELETE(pTextureStream);
		return false;
	}

	png_infop pPngInfo = png_create_info_struct(pPngStruct);
	if (!pPngInfo)
	{
		png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
		// TODO: logout
		SAFE_DELETE(pTextureStream);
		return false;
	}

	if (setjmp(png_jmpbuf(pPngStruct)))
	{
		png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
		// TODO: logout
		SAFE_DELETE(pTextureStream);
		return false;
	}

	//define our own callback function for I/O instead of reading from a file
	png_set_read_fn(pPngStruct, pTextureStream, pngReaderCallback);

	png_read_info(pPngStruct, pPngInfo);
	m_nWidth = png_get_image_width(pPngStruct, pPngInfo);
	m_nHeight = png_get_image_height(pPngStruct, pPngInfo);
	png_byte nColorType = png_get_color_type(pPngStruct, pPngInfo);	//可以是PNG_COLOR_TYPE_RGB,PNG_COLOR_TYPE_PALETTE.......等
	png_byte nBitDepth = png_get_bit_depth(pPngStruct, pPngInfo);
	int nRowBytes = png_get_rowbytes(pPngStruct, pPngInfo);

	// Convert stuff to appropriate formats!
	if(nColorType == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_packing(pPngStruct);
		png_set_palette_to_rgb(pPngStruct); //Expand data to 24-bit RGB or 32-bit RGBA if alpha available.
	}

	// TODO: why?
	if (nColorType == PNG_COLOR_TYPE_GRAY && nBitDepth < 8) png_set_expand_gray_1_2_4_to_8(pPngStruct);
	if (nColorType == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(pPngStruct);
	if (nBitDepth == 16) png_set_strip_16(pPngStruct);

	//Expand paletted or RGB images with transparency to full alpha channels so the data will be available as RGBA quartets.
	if(png_get_valid(pPngStruct, pPngInfo, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(pPngStruct);
	}

	// read image data into pRowPointers
	uchar** pRowPointers = new uchar*[m_nHeight];
	for (uint y = 0; y < m_nHeight; y++)
	{
		pRowPointers[y] = new uchar[m_nWidth * 4]; //each pixel(RGBA) has 4 bytes
	}
	png_read_image(pPngStruct, pRowPointers);

	// store image data into our pRGBAData
	m_pTextureDataRGBA = new uchar[m_nWidth * m_nHeight * 4];  //each pixel(RGBA) has 4 bytes
	//unlike store the pixel data from top-left corner, store them from bottom-left corner for OGLES Texture drawing...
	int nCurrPos = (m_nWidth * m_nHeight * 4) - (4 * m_nWidth);
	for(uint row = 0; row < m_nHeight; row++)
	{
		for(uint col = 0; col < (4 * m_nWidth); col += 4)
		{
			m_pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col];        // red
			m_pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col + 1];    // green
			m_pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col + 2];    // blue
			m_pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col + 3];    // alpha
		}
		nCurrPos = (nCurrPos - (m_nWidth * 4) * 2); //move the pointer back two rows
	}

	//clean up after the read, and free any memory allocated
	// free pRowPointers
	for (uint y = 0; y < m_nHeight; y++)
	{
		SAFE_DELETE_ARRAY(pRowPointers[y]);
	}
	SAFE_DELETE_ARRAY(pRowPointers);
	png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
	SAFE_DELETE(pTextureStream);

	return true;
}

void Texture_Impl::FreeTextureData()
{
	SAFE_DELETE_ARRAY(m_pTextureDataRGBA);
	m_nWidth = 0;
	m_nHeight = 0;
}

bool Texture_Impl::CreateGLTexture()
{
	FreeGLTexture();

	glGenTextures(1, &m_nGLTextureID);
	if (m_nGLTextureID == 0) return false;

	glBindTexture(GL_TEXTURE_2D, m_nGLTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pTextureDataRGBA);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return true;
}

void Texture_Impl::FreeGLTexture()
{
	if (m_nGLTextureID != 0)
	{
		glDeleteTextures(1, &m_nGLTextureID);
		m_nGLTextureID = 0;
	}
}

GLuint Texture_Impl::GetGLTextureID() const
{
	return m_nGLTextureID;
}
