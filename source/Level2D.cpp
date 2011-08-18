/*!
 * \file Level2D_Impl.cpp
 * \date 08-08-2011 22:49:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <Level2D.h>
#include <math/IMath.h>
#include <util/IFileUtil.h>
#include <util/ScreenUtil.h>
#include <ITextureMgr.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>

Level2D::Level2D(const char* pszLevel2DFile)
{
	m_CenterPosition.x = 0;
	m_CenterPosition.y = 0;
	m_PrvCenterPosition = m_CenterPosition;

	IMath::BuildIdentityMatrix(m_ModelMatrix);
	m_nHalfSceneHeight = ScreenUtil::GetInstance().GetScreenHeight()/2;
	m_nHalfSceneWidth = ScreenUtil::GetInstance().GetScreenWidth()/2;
	m_nHalfBuffersize = 3;
	m_pTexture = NULL;
	m_pIndis = NULL;
	m_pVerts = NULL;
	m_pShader = NULL;
	m_pGidAry = NULL;
	m_pMapFlag = NULL;
	m_bOK = LoadLevel2DFromFile(pszLevel2DFile);
}

Level2D::~Level2D()
{
	// TODO: 
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE_ARRAY(m_pVerts);
	SAFE_RELEASE(m_pShader);
	SAFE_DELETE_ARRAY(m_pGidAry);
	SAFE_DELETE_ARRAY(m_TILEINFO);
}

void Level2D::Update(float dt)
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

void Level2D::Render()
{
	m_pShader->SetTexture("u_texture",m_pTexture);

	// Set Model matrix
	Vector2 m_Translate = m_CenterPosition - m_PrvCenterPosition;
	m_ModelMatrix.Translate(-m_Translate.x, -m_Translate.y, 0);
	IRenderer2D::GetInstance().SetModelViewMatrix(m_ModelMatrix);

	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	uint nXTileSize =(m_nHalfSceneWidth / m_FILEHEADER.nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	uint nYTileSize = (m_nHalfSceneHeight / m_FILEHEADER.nTileHeight) * 2+m_nHalfBuffersize * 2;
	uint unRectSize = nXTileSize * nYTileSize;
	IRenderer2D::GetInstance().DrawTriangleList(m_pVerts,unRectSize * 4,m_pIndis,unRectSize*6,m_pShader);
	IMath::BuildIdentityMatrix(m_ModelMatrix);
}

void Level2D::SetCenterPosition(const Vector2& pos)
{
	// TODO:
	m_CenterPosition = pos;
	
}

const Vector2& Level2D::GetCenterPosition() const
{
	// TODO: 
	return m_CenterPosition;
}

bool Level2D::LoadLevel2DFromFile(const char* pszLevel2DFile)
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
	SAFE_DELETE_ARRAY(m_pIndis);
	m_pIndis = new ushort[nXTileSize * nYTileSize * 6];
	SAFE_DELETE_ARRAY(m_pMapFlag);
	m_pMapFlag = new bool[nXTileSize *nYTileSize];
	//First InitVerts,the function only be used once;
	InitVerts();
	return true;
}
void Level2D::C2TextTureCoordinate(Vector2 MapPosition,int& nXindex, int& nYindex)
{
	MapPosition.x = m_FILEHEADER.nMapCol * m_FILEHEADER.nTileWidth / 2 + MapPosition.x;
	MapPosition.y = m_FILEHEADER.nMapRow * m_FILEHEADER.nTileHeight/ 2 - MapPosition.y;  
	
	nXindex = (int)MapPosition.x/ (int)m_FILEHEADER.nTileWidth;
	nYindex = (int)MapPosition.y / (int)m_FILEHEADER.nTileHeight;
	
}

void Level2D::InitVerts()
{
	int nXTileSize =(m_nHalfSceneWidth / m_FILEHEADER.nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	int nYTileSize = (m_nHalfSceneHeight / m_FILEHEADER.nTileHeight) * 2 + m_nHalfBuffersize * 2;
	//Init Start Coordinate
	float fXstartCoord = -float(nXTileSize / 2) * m_FILEHEADER.nTileWidth;
	float fYstartCoord =  float(nYTileSize / 2) * m_FILEHEADER.nTileHeight;
	//TextTrue off 
	int nXindex = 0;
	int nYindex = 0;
	Vector2 TextTrueCoordinate;
	TextTrueCoordinate.x = fXstartCoord + m_PrvCenterPosition.x;
	TextTrueCoordinate.y = fYstartCoord + m_PrvCenterPosition.y;
	C2TextTureCoordinate(TextTrueCoordinate, nXindex, nYindex);

	for(int v1=0; v1 < nYTileSize; v1++)
	{
		for ( int v2=0; v2 < nXTileSize; v2++ )
		{
			//Set the Indis Array;
			//	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};
			int startIndis = v1 * nXTileSize * 6 + v2* 6;
			//Set screen triangular element
			uint noff = v1 * nXTileSize *4 +	v2 * 4;
			m_pIndis[startIndis] = noff;
			m_pIndis[startIndis + 1] = noff + 1;
			m_pIndis[startIndis + 2] = noff + 2;
			m_pIndis[startIndis + 3] = noff + 1;
			m_pIndis[startIndis + 4] = noff + 3;
			m_pIndis[startIndis + 5] = noff + 2;
			
			if(nXindex < (int)m_FILEHEADER.nMapCol
				&&nXindex >= 0
				&&nYindex < (int)m_FILEHEADER.nMapRow
				&&nYindex >= 0)
			{
				uint MapIndex = m_pGidAry[nYindex* m_FILEHEADER.nMapCol + nXindex];
				m_pVerts[noff].x = fXstartCoord;
				m_pVerts[noff].y = fYstartCoord - m_FILEHEADER.nTileHeight;
				m_pVerts[noff].z = 0.0f;
				m_pVerts[noff].u =m_TILEINFO[MapIndex].u;
				m_pVerts[noff].v =m_TILEINFO[MapIndex].v;

				m_pVerts[noff +1].x = fXstartCoord;
				m_pVerts[noff +1].y = fYstartCoord;
				m_pVerts[noff +1].z = 0.0f;
				m_pVerts[noff +1].u = m_TILEINFO[MapIndex].u;
				m_pVerts[noff +1].v = m_TILEINFO[MapIndex].v + m_TILEINFO[MapIndex].dv;

				m_pVerts[noff +2].x = fXstartCoord + m_FILEHEADER.nTileWidth;
				m_pVerts[noff +2].y = fYstartCoord - m_FILEHEADER.nTileHeight;
				m_pVerts[noff +2].z = 0.0f;
				m_pVerts[noff +2].u = m_TILEINFO[MapIndex].u + m_TILEINFO[MapIndex].du ;
				m_pVerts[noff +2].v = m_TILEINFO[MapIndex].v ; 

				m_pVerts[noff +3].x = fXstartCoord + m_FILEHEADER.nTileWidth;
				m_pVerts[noff +3].y = fYstartCoord;
				m_pVerts[noff +3].z = 0.0f;
				m_pVerts[noff +3].u = m_TILEINFO[MapIndex].u + m_TILEINFO[MapIndex].du;
				m_pVerts[noff +3].v = m_TILEINFO[MapIndex].v + m_TILEINFO[MapIndex].dv;
			}
			else
			{
				m_pVerts[noff].x = fXstartCoord;
				m_pVerts[noff].y = fYstartCoord - m_FILEHEADER.nTileHeight;
				m_pVerts[noff].z = 0.0f;
				m_pVerts[noff].u =m_TILEINFO[m_FILEHEADER.nDefaultTile].u;
				m_pVerts[noff].v =m_TILEINFO[m_FILEHEADER.nDefaultTile].v;

				m_pVerts[noff +1].x = fXstartCoord;
				m_pVerts[noff +1].y = fYstartCoord;
				m_pVerts[noff +1].z = 0.0f;
				m_pVerts[noff +1].u = m_TILEINFO[m_FILEHEADER.nDefaultTile].u;
				m_pVerts[noff +1].v = m_TILEINFO[m_FILEHEADER.nDefaultTile].v + m_TILEINFO[m_FILEHEADER.nDefaultTile].dv;

				m_pVerts[noff +2].x = fXstartCoord + m_FILEHEADER.nTileWidth;
				m_pVerts[noff +2].y = fYstartCoord - m_FILEHEADER.nTileHeight;
				m_pVerts[noff +2].z = 0.0f;
				m_pVerts[noff +2].u = m_TILEINFO[m_FILEHEADER.nDefaultTile].u + m_TILEINFO[m_FILEHEADER.nDefaultTile].du ;
				m_pVerts[noff +2].v = m_TILEINFO[m_FILEHEADER.nDefaultTile].v ; 

				m_pVerts[noff +3].x = fXstartCoord + m_FILEHEADER.nTileWidth;
				m_pVerts[noff +3].y = fYstartCoord;
				m_pVerts[noff +3].z = 0.0f;
				m_pVerts[noff +3].u = m_TILEINFO[m_FILEHEADER.nDefaultTile].u + m_TILEINFO[m_FILEHEADER.nDefaultTile].du;
				m_pVerts[noff +3].v = m_TILEINFO[m_FILEHEADER.nDefaultTile].v + m_TILEINFO[m_FILEHEADER.nDefaultTile].dv;
			}
			//Add  a off distance to iXstarCoord
			fXstartCoord += m_FILEHEADER.nTileWidth;
			nXindex++;
		}
		//go to next Row, add a off distance to fYstarCoord
		nXindex -= nXTileSize;
		nYindex++;
		fXstartCoord = - (float)(nXTileSize / 2) * m_FILEHEADER.nTileWidth;
		fYstartCoord -= m_FILEHEADER.nTileHeight;
	}
}
void Level2D::UpdateVerts()
{
	int nXTileSize =(m_nHalfSceneWidth / m_FILEHEADER.nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	int nYTileSize = (m_nHalfSceneHeight / m_FILEHEADER.nTileHeight) * 2 + m_nHalfBuffersize * 2;
	//Init Start Coordinate
	float fXstartCoord = -float(nXTileSize / 2) * m_FILEHEADER.nTileWidth;
	float fYstartCoord =  float(nYTileSize / 2) * m_FILEHEADER.nTileHeight;
	//TextTrue off 
	int nXindex = 0;
	int nYindex = 0;
	Vector2 TextTrueCoordinate;
	TextTrueCoordinate.x = fXstartCoord + m_PrvCenterPosition.x;
	TextTrueCoordinate.y = fYstartCoord + m_PrvCenterPosition.y;
	C2TextTureCoordinate(TextTrueCoordinate, nXindex, nYindex);

	for(int v1=0; v1 < nYTileSize; v1++)
	{
		for ( int v2=0; v2 < nXTileSize; v2++ )
		{
			//
			//Post IniteVerts,Only need to update the texture coordinates
			int noff = v1 * nXTileSize *4 +	v2 * 4;
			
			if(nXindex < (int)m_FILEHEADER.nMapCol
				&&nXindex >= 0
				&&nYindex < (int)m_FILEHEADER.nMapRow
				&&nYindex >= 0)
			{
				uint MapIndex = m_pGidAry[nYindex* m_FILEHEADER.nMapCol + nXindex];
				m_pVerts[noff].u =m_TILEINFO[MapIndex].u;
				m_pVerts[noff].v =m_TILEINFO[MapIndex].v;

				m_pVerts[noff +1].u = m_TILEINFO[MapIndex].u;
				m_pVerts[noff +1].v = m_TILEINFO[MapIndex].v + m_TILEINFO[MapIndex].dv;
				
				m_pVerts[noff +2].u = m_TILEINFO[MapIndex].u + m_TILEINFO[MapIndex].du ;
				m_pVerts[noff +2].v = m_TILEINFO[MapIndex].v ; 
				
				m_pVerts[noff +3].u = m_TILEINFO[MapIndex].u + m_TILEINFO[MapIndex].du;
				m_pVerts[noff +3].v = m_TILEINFO[MapIndex].v + m_TILEINFO[MapIndex].dv;
			}
			else
			{
				
				
				m_pVerts[noff].u =m_TILEINFO[m_FILEHEADER.nDefaultTile].u;
				m_pVerts[noff].v =m_TILEINFO[m_FILEHEADER.nDefaultTile].v;

				m_pVerts[noff +1].u = m_TILEINFO[m_FILEHEADER.nDefaultTile].u;
				m_pVerts[noff +1].v = m_TILEINFO[m_FILEHEADER.nDefaultTile].v + m_TILEINFO[m_FILEHEADER.nDefaultTile].dv;

				m_pVerts[noff +2].u = m_TILEINFO[m_FILEHEADER.nDefaultTile].u + m_TILEINFO[m_FILEHEADER.nDefaultTile].du ;
				m_pVerts[noff +2].v = m_TILEINFO[m_FILEHEADER.nDefaultTile].v ; 

				m_pVerts[noff +3].u = m_TILEINFO[m_FILEHEADER.nDefaultTile].u + m_TILEINFO[m_FILEHEADER.nDefaultTile].du;
				m_pVerts[noff +3].v = m_TILEINFO[m_FILEHEADER.nDefaultTile].v + m_TILEINFO[m_FILEHEADER.nDefaultTile].dv;
			}
			//Add  a off distance to fXstarCoord
			fXstartCoord += m_FILEHEADER.nTileWidth;
			nXindex++;
		}
		//go to next Row, add a off distance to fYstarCoord
		nXindex-= nXTileSize;
		nYindex++;
		fXstartCoord = - (float)(nXTileSize / 2) * m_FILEHEADER.nTileWidth;
		fYstartCoord -= m_FILEHEADER.nTileHeight;
	}
}