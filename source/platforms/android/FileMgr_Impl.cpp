/*!
 * \file FileMgr_Impl.cpp
 * \date 7-20-2011 10:59:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileMgr_Impl.h"
#include <IDebugUtil.h>
#include <IConfig.h>
#include <util/StreamWriter.h>
#include <lpng154/png.h>

IFileMgr& IFileMgr::GetInstance()
{
	static FileMgr_Impl s_FileMgr_Impl;
	return s_FileMgr_Impl;
}

static void PngReaderCallback(png_structp pPngStruct, png_bytep pData, png_size_t nSize)
{
	StreamReader* pStream = (StreamReader*)png_get_io_ptr(pPngStruct);

	if (!pStream->Read(pData, nSize))
	{
		png_error(pPngStruct,"pngReaderCallback failed");
	}
}

FileMgr_Impl::FileMgr_Impl()
{
	m_pMainFile = NULL;
}

FileMgr_Impl::~FileMgr_Impl()
{
	// TODO: 
}

bool FileMgr_Impl::Initialize()
{
	const char* pszPackageFilePath = IConfig::GetInstance().GetString("ANDROID_RESOURCE_PACKAGE");
	if (!pszPackageFilePath || strlen(pszPackageFilePath) <= 0)
	{
		LOGE("invalid resource package path");
		return false;
	}

	m_pMainFile = unzOpen(pszPackageFilePath);
	if (!m_pMainFile)
	{
		LOGE("open resource package file failed: %s", pszPackageFilePath);
		return false;
	}

	m_strRootPath = IConfig::GetInstance().GetString("RESOURCE_DIR", "assets/");
	LOGD("resource directory: %s", m_strRootPath.c_str());

	return true;
}

void FileMgr_Impl::Terminate()
{
	if (m_pMainFile)
	{
		unzClose(m_pMainFile);
		m_pMainFile = NULL;
	}
}

StreamReader* FileMgr_Impl::LoadFile(const char* pszFileName)
{
	if (!pszFileName || strlen(pszFileName) <= 0) return NULL;

	std::string strFullPath = m_strRootPath + pszFileName;

	int nRet = unzLocateFile(m_pMainFile, strFullPath.c_str(), 1);
	if (nRet != UNZ_OK)
	{
		LOGE("locate file failed: %s", strFullPath.c_str());
		return NULL;
	}

	char szFilePath[MAX_FILE_PATH];
	unz_file_info fileInfo;
	nRet = unzGetCurrentFileInfo(m_pMainFile, &fileInfo, szFilePath, sizeof(szFilePath), NULL, 0, NULL, 0);
	if (nRet != UNZ_OK)
	{
		LOGE("get file info failed: %s", strFullPath.c_str());
		return NULL;
	}

	nRet = unzOpenCurrentFile(m_pMainFile);
	if (nRet != UNZ_OK)
	{
		LOGE("open file failed: %s", szFilePath);
		return NULL;
	}

	int nFileSize = fileInfo.uncompressed_size;
	char* pszBuffer = new char[nFileSize+1];
	int nReadSize = unzReadCurrentFile(m_pMainFile, pszBuffer, nFileSize);
	if (nReadSize != nFileSize)
	{
		LOGE("read size miss-match: %d/%d read", nReadSize, nFileSize);
	}
	unzCloseCurrentFile(m_pMainFile);

	pszBuffer[nFileSize] = '\0';

	StreamReader* pStreamReader = new StreamReader(pszBuffer, nFileSize, true);
	return pStreamReader;
}

StreamReader* FileMgr_Impl::LoadImageFile(const char* pszFileName, uint* pnWidth, uint* pnHeight)
{
	StreamReader* pTextureStream = LoadFile(pszFileName);
	if (!pTextureStream || !pTextureStream->IsOK())
	{
		SAFE_RELEASE(pTextureStream);
		return false;
	}

	png_structp pPngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!pPngStruct)
	{
		png_destroy_read_struct(&pPngStruct, NULL, NULL);
		// logout
		LOGE("load image file failed: %s", pszFileName);
		SAFE_DELETE(pTextureStream);
		return false;
	}

	png_infop pPngInfo = png_create_info_struct(pPngStruct);
	if (!pPngInfo)
	{
		png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
		// logout
		LOGE("create png info failed: %s", pszFileName);
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
	png_set_read_fn(pPngStruct, pTextureStream, PngReaderCallback);

	png_read_info(pPngStruct, pPngInfo);
	int nTextureWidth = png_get_image_width(pPngStruct, pPngInfo);
	int nTextureHeight = png_get_image_height(pPngStruct, pPngInfo);
	png_byte nColorType = png_get_color_type(pPngStruct, pPngInfo);	//可以是PNG_COLOR_TYPE_RGB,PNG_COLOR_TYPE_PALETTE.......等
	png_byte nBitDepth = png_get_bit_depth(pPngStruct, pPngInfo);

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
	uchar** pRowPointers = new uchar*[nTextureHeight];
	for (int y = 0; y < nTextureHeight; y++)
	{
		pRowPointers[y] = new uchar[nTextureWidth * 4]; //each pixel(RGBA) has 4 bytes
	}
	png_read_image(pPngStruct, pRowPointers);

	// free the stream object and png structure
	png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
	SAFE_RELEASE(pTextureStream);

	// store image data into our pRGBAData
	uchar* pTextureDataRGBA = new uchar[nTextureWidth * nTextureHeight * 4];  //each pixel(RGBA) has 4 bytes
	//unlike store the pixel data from top-left corner, store them from bottom-left corner for OGLES Texture drawing...
	int nCurrPos = (nTextureWidth * nTextureHeight * 4) - (4 * nTextureWidth);
	for(int row = 0; row < nTextureHeight; row++)
	{
		for(int col = 0; col < (4 * nTextureWidth); col += 4)
		{
			pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col];        // red
			pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col + 1];    // green
			pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col + 2];    // blue
			pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col + 3];    // alpha
		}
		nCurrPos = (nCurrPos - (nTextureWidth * 4) * 2); //move the pointer back two rows
	}

	// free pRowPointers
	for (int y = 0; y < nTextureHeight; y++)
	{
		SAFE_DELETE_ARRAY(pRowPointers[y]);
	}
	SAFE_DELETE_ARRAY(pRowPointers);

	StreamReader* pStreamReader = new StreamReader(pTextureDataRGBA, nTextureWidth * nTextureHeight * 4, true);
	if (!pStreamReader || !pStreamReader->IsOK())
	{
		LOGE("create texture stream reader failed with texture size: %d", nTextureWidth * nTextureHeight * 4);
		SAFE_DELETE(pStreamReader);
		SAFE_DELETE_ARRAY(pTextureDataRGBA);
		return NULL;
	}

	*pnWidth = nTextureWidth;
	*pnHeight = nTextureHeight;
	return pStreamReader;
}
