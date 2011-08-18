/*!
 * \file Level2D_Impl.cpp
 * \date 08-08-2011 22:49:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Level2D_Impl.h"
#include <math/IMath.h>
#include <util/IFileUtil.h>
#include <util/ScreenUtil.h>
#include <ITextureMgr.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>
#include <tinyxml-2.6.2/tinyxml.h>

Level2D_Impl::Level2D_Impl(const char* pszLevel2DFile)
{
	
	m_CenterPosition.x = 0;
	m_CenterPosition.y = 0;
	m_PrvCenterPosition = m_CenterPosition;

	IMath::BuildIdentityMatrix(m_ModelMatrix);
	m_nHalfSceneHeight = ScreenUtil::GetInstance().GetScreenHeight()/2;
	m_nHalfSceneWidth = ScreenUtil::GetInstance().GetScreenWidth()/2;
	m_nHalfBuffersize = 3;
	m_pTexture = NULL;
	m_pVerts = NULL;
	m_pShader = NULL;
	m_pGidAry = NULL;
	m_pMapFlag = NULL;
	m_bOK = LoadLevel2DFromFile(pszLevel2DFile);
}

Level2D_Impl::~Level2D_Impl()
{
	// TODO: 
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE_ARRAY(m_pVerts);
	SAFE_DELETE(m_pShader);
	SAFE_DELETE_ARRAY(m_pGidAry);
	SAFE_DELETE_ARRAY(m_TILEINFO);
}

ILevel2D* ILevel2D::CreateLevel2D(const char* pszLevel2DFile)
{
	Level2D_Impl* pLevel2D =  new Level2D_Impl(pszLevel2DFile);
	if (!pLevel2D || !pLevel2D->IsOK())
	{
		SAFE_DELETE(pLevel2D);
		return NULL;
	}
	return pLevel2D;
}

void Level2D_Impl::Update(float dt)
{
	//Calculation of boundary values
	int nXBoundary = (m_nHalfBuffersize + (m_nHalfSceneWidth/m_FILEHEADER.nTileWidth)) * m_FILEHEADER.nTileWidth - m_nHalfSceneWidth;
	int nYBoundary = (m_nHalfBuffersize + (m_nHalfSceneHeight/m_FILEHEADER.nTileHeight)) * m_FILEHEADER.nTileHeight - m_nHalfSceneHeight;
	
	//Judge whether beyond boundaries
	if((m_CenterPosition.x - m_PrvCenterPosition.x > nXBoundary)
		||(m_CenterPosition.x - m_PrvCenterPosition.x < -nXBoundary)
		||((m_CenterPosition.y - m_PrvCenterPosition.y) > nYBoundary)
		||(m_CenterPosition.y - m_PrvCenterPosition.y < -nYBoundary))
	{
		// If the scene surface out of current surface, must Update the Verts,to show a new surface;
		m_PrvCenterPosition.x =  int(m_CenterPosition.x/(int) m_FILEHEADER.nTileWidth) * (int) m_FILEHEADER.nTileWidth;
		m_PrvCenterPosition.y =  int(m_CenterPosition.y/ (int)m_FILEHEADER.nTileHeight) * (int)m_FILEHEADER.nTileHeight;
		//Update the Verts
		UpdateVerts();
	}
}

void Level2D_Impl::Render()
{
	m_pShader->SetTexture("u_texture",m_pTexture);

	// Set Model matrix
	Vector2 m_Translate = m_CenterPosition - m_PrvCenterPosition;
	m_ModelMatrix.Translate(-m_Translate.x, -m_Translate.y, 0);
	IRenderer2D::GetInstance().SetModelViewMatrix(m_ModelMatrix);

	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	int nXTileSize =(m_nHalfSceneWidth / m_FILEHEADER.nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	int nYTileSize = (m_nHalfSceneHeight / m_FILEHEADER.nTileHeight) * 2+m_nHalfBuffersize * 2;
	for(int y = 0; y < nYTileSize; y++)
	{	
		for (int x =0; x <nXTileSize; x++)
		{
			int index = y*nXTileSize +x;
			if(m_pMapFlag[index])
				IRenderer2D::GetInstance().DrawRect(&m_pVerts[index * 4], m_pShader);
		}
	}
	IMath::BuildIdentityMatrix(m_ModelMatrix);
}

void Level2D_Impl::SetCenterPosition(const Vector2& pos)
{
	// TODO:
	m_CenterPosition = pos;
	
}

const Vector2& Level2D_Impl::GetCenterPosition() const
{
	// TODO: 
	return m_CenterPosition;
}

bool Level2D_Impl::LoadLevel2DFromFile(const char* pszLevel2DFile)
{
	//parse the L2D file
	StreamReader* pReader = IFileUtil::GetInstance().LoadFile(pszLevel2DFile);
	if (!pReader) return false;
	pReader->Reset();
	pReader->Read(&m_FILEHEADER,sizeof(m_FILEHEADER));
	m_TILEINFO = new FmtL2D::TILE_INFO[m_FILEHEADER.nNumTiles];
	pReader->Read(m_TILEINFO,sizeof(FmtL2D::TILE_INFO)* m_FILEHEADER.nNumTiles);
	m_pGidAry = new uint[m_FILEHEADER.nMapCol* m_FILEHEADER.nMapRow];
	pReader->Read(m_pGidAry,sizeof(uint)*m_FILEHEADER.nMapCol* m_FILEHEADER.nMapRow);
	
	//Set the shader and the TextTure
	m_pShader = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
	if(!m_pShader) return false;
	m_pTexture = ITextureMgr::GetInstance().CreateTexture(m_FILEHEADER.szTextureFile);
	if(NULL == m_pTexture) return false;
	
	//Set the date Container. 
	int nXTileSize =(m_nHalfSceneWidth / m_FILEHEADER.nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	int nYTileSize = (m_nHalfSceneHeight / m_FILEHEADER.nTileHeight) * 2+m_nHalfBuffersize * 2;
	SAFE_DELETE_ARRAY(m_pVerts);
	m_pVerts = new VATTR_POS_UV[nXTileSize * nYTileSize * 4 ];
	SAFE_DELETE_ARRAY(m_pMapFlag);
	m_pMapFlag = new bool[nXTileSize *nYTileSize];
	//First InitVerts,the function only be used once;
	InitVerts();
	return true;
}
bool Level2D_Impl::C2TextTureCoordinate(Vector2& MapPosition,uint& index )
{
	//Calculation in map coordinates
	MapPosition.x = m_FILEHEADER.nMapCol * m_FILEHEADER.nTileWidth / 2 + MapPosition.x;
	MapPosition.y = m_FILEHEADER.nMapRow * m_FILEHEADER.nTileHeight/ 2 - MapPosition.y;   
	uint indexX = (uint)MapPosition.x / m_FILEHEADER.nTileWidth;
	uint indexY = (uint)MapPosition.y / m_FILEHEADER.nTileHeight;
	if(indexX >= m_FILEHEADER.nMapCol || indexY >= m_FILEHEADER.nMapRow)
		return false;
	//Get Index in the mGidAry, the Array to show the TextTure in the map position
	index = m_pGidAry[indexY * m_FILEHEADER.nMapCol + indexX];
	if(index >= m_FILEHEADER.nNumTiles)
		return false;
	//Get the TextTure coordinate
	MapPosition.x = m_TILEINFO[index].u;
	MapPosition.y = m_TILEINFO[index].v;
	return true;
}
void Level2D_Impl::InitVerts()
{
	int nXTileSize =(m_nHalfSceneWidth / m_FILEHEADER.nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	int nYTileSize = (m_nHalfSceneHeight / m_FILEHEADER.nTileHeight) * 2 + m_nHalfBuffersize * 2;
	//Init Start Coordinate
	float fXstartCoord = -float(nXTileSize / 2) * m_FILEHEADER.nTileWidth;
	float fYstartCoord =  float(nYTileSize / 2) * m_FILEHEADER.nTileHeight;
	//TextTrue off 
	Vector2 TextTrueCoordinate;

	for(int v1=0; v1 < nYTileSize; v1++)
	{
		for ( int v2=0; v2 < nXTileSize; v2++ )
		{
			//Set screen triangular element
			int noff = v1 * nXTileSize *4 +	v2 * 4;
			Vector2 TextTrueCoordinate;
			uint index = 0;
			TextTrueCoordinate.x = fXstartCoord + m_PrvCenterPosition.x;
			TextTrueCoordinate.y = fYstartCoord + m_PrvCenterPosition.y;
			m_pMapFlag[v1 * nXTileSize +v2]= C2TextTureCoordinate(TextTrueCoordinate, index);
			m_pVerts[noff].x = fXstartCoord;
			m_pVerts[noff].y = fYstartCoord - m_FILEHEADER.nTileHeight;
			m_pVerts[noff].z = 0.0f;
			m_pVerts[noff].u =m_TILEINFO[index].u;
			m_pVerts[noff].v =m_TILEINFO[index].v;

			m_pVerts[noff +1].x = fXstartCoord;
			m_pVerts[noff +1].y = fYstartCoord;
			m_pVerts[noff +1].z = 0.0f;
			m_pVerts[noff +1].u = m_TILEINFO[index].u;
			m_pVerts[noff +1].v = m_TILEINFO[index].v + m_TILEINFO[index].dv;

			m_pVerts[noff +2].x = fXstartCoord + m_FILEHEADER.nTileWidth;
			m_pVerts[noff +2].y = fYstartCoord - m_FILEHEADER.nTileHeight;
			m_pVerts[noff +2].z = 0.0f;
			m_pVerts[noff +2].u = TextTrueCoordinate.x + m_TILEINFO[index].du ;
			m_pVerts[noff +2].v = TextTrueCoordinate.y ; 

			m_pVerts[noff +3].x = fXstartCoord + m_FILEHEADER.nTileWidth;
			m_pVerts[noff +3].y = fYstartCoord;
			m_pVerts[noff +3].z = 0.0f;
			m_pVerts[noff +3].u = TextTrueCoordinate.x + m_TILEINFO[index].du;
			m_pVerts[noff +3].v = TextTrueCoordinate.y + m_TILEINFO[index].dv;

			//Add  a off distance to iXstarCoord
			fXstartCoord += m_FILEHEADER.nTileWidth;
		}
		//go to next Row, add a off distance to fYstarCoord
		fXstartCoord = - (float)(nXTileSize / 2) * m_FILEHEADER.nTileWidth;
		fYstartCoord -= m_FILEHEADER.nTileHeight;
	}
}
void Level2D_Impl::UpdateVerts()
{
	int nXTileSize =(m_nHalfSceneWidth / m_FILEHEADER.nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	int nYTileSize = (m_nHalfSceneHeight / m_FILEHEADER.nTileHeight) * 2 + m_nHalfBuffersize * 2;
	//Init Start Coordinate
	float fXstartCoord = -float(nXTileSize / 2) * m_FILEHEADER.nTileWidth;
	float fYstartCoord =  float(nYTileSize / 2) * m_FILEHEADER.nTileHeight;
	//TextTrue off 
	Vector2 TextTrueCoordinate;

	for(int v1=0; v1 < nYTileSize; v1++)
	{
		for ( int v2=0; v2 < nXTileSize; v2++ )
		{
			//Post IniteVerts,Only need to update the texture coordinates
			int noff = v1 * nXTileSize *4 +	v2 * 4;
			Vector2 TextTrueCoordinate;
			uint index = 0;
			TextTrueCoordinate.x = fXstartCoord + m_PrvCenterPosition.x;
			TextTrueCoordinate.y = fYstartCoord + m_PrvCenterPosition.y;
			m_pMapFlag[v1 * nXTileSize +v2]= C2TextTureCoordinate(TextTrueCoordinate, index);

			m_pVerts[noff].u =m_TILEINFO[index].u;
			m_pVerts[noff].v =m_TILEINFO[index].v;

			m_pVerts[noff +1].u = m_TILEINFO[index].u;
			m_pVerts[noff +1].v = m_TILEINFO[index].v + m_TILEINFO[index].dv;
			
			m_pVerts[noff +2].u = TextTrueCoordinate.x + m_TILEINFO[index].du ;
			m_pVerts[noff +2].v = TextTrueCoordinate.y ; 
			
			m_pVerts[noff +3].u = TextTrueCoordinate.x + m_TILEINFO[index].du;
			m_pVerts[noff +3].v = TextTrueCoordinate.y + m_TILEINFO[index].dv;

			//Add  a off distance to fXstarCoord
			fXstartCoord += m_FILEHEADER.nTileWidth;

		}
		//go to next Row, add a off distance to fYstarCoord
		fXstartCoord = - (float)(nXTileSize / 2) * m_FILEHEADER.nTileWidth;
		fYstartCoord -= m_FILEHEADER.nTileHeight;
	}
}