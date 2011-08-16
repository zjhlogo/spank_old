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
	
	m_TexturePosition = m_CenterPosition;
	
	m_nCenterPositionX = 0;
	m_nCenterPositionY = 0;
	m_nPrvCenterPositionX = 0;
	m_nPrvCenterPositionY = 0;
	
	m_nCurrenSurfaceOffX = 0;
	m_nCurrenSurfaceOffY = 0;
	
	m_nLayerWidth = 0;
	m_nLayerHeight = 0;

	m_nTileWidth = 0;
	m_nTildHeight = 0;

	IMath::BuildIdentityMatrix(m_ModleMatrix);
	m_nHalfSceneHeight = ScreenUtil::GetInstance().GetScreenHeight()/2;
	m_nHalfSceneWidth = ScreenUtil::GetInstance().GetScreenWidth()/2;
	m_nHalfBuffersize = 3;
	
	m_pGidAry = NULL;
	m_pTexture = NULL;
	m_pVerts = NULL;
	m_pShader = NULL;
	
	m_bOK = LoadLevel2DFromFile(pszLevel2DFile);
}

Level2D_Impl::~Level2D_Impl()
{
	// TODO: 
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE_ARRAY(m_pGidAry);
	SAFE_DELETE_ARRAY(m_pVerts);
	SAFE_DELETE(m_pShader);
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
	// TODO:
	
	if(m_nCenterPositionX == m_nPrvCenterPositionX && m_nCenterPositionY == m_nPrvCenterPositionY)
		return;

	int nXBoundary = (m_nHalfBuffersize + (m_nHalfSceneWidth/m_nTileWidth)) * m_nTileWidth - m_nHalfSceneWidth;
	int nYBoundary = (m_nHalfBuffersize + (m_nHalfSceneHeight/m_nTildHeight)) * m_nTildHeight - m_nHalfSceneHeight;

	if((m_nCenterPositionX - m_nPrvCenterPositionX > nXBoundary)
		||(m_nCenterPositionX - m_nPrvCenterPositionX < -nXBoundary)
		||((m_nCenterPositionY - m_nPrvCenterPositionY) > nYBoundary)
		||(m_nCenterPositionY - m_nPrvCenterPositionY < -nYBoundary))
	{
		int TranslateX = 0;
		int TranslateY = 0;
		m_TexturePosition.x = (m_CenterPosition.x / m_nTileWidth) * m_nTileWidth;
		m_TexturePosition.y = (m_CenterPosition.y/ m_nTildHeight) * m_nTildHeight;
		
		TranslateX = m_nCenterPositionX - (int)m_TexturePosition.x;
		TranslateY = m_nCenterPositionY - (int)m_TexturePosition.y;

		m_nCurrenSurfaceOffX = TranslateX;
		m_nCurrenSurfaceOffY = TranslateY;
		InitVerts();
		IMath::BuildIdentityMatrix(m_ModleMatrix);
		Matrix4x4 TranlateMatrix;
		IMath::BuildIdentityMatrix(TranlateMatrix);
		TranlateMatrix.Translate(-TranslateX,-TranslateY, 0);
		m_ModleMatrix *= TranlateMatrix;	
	}
	else
	{
		//Translate
		int TranslateX = 0;
		int TranslateY = 0;
		TranslateX =  m_nCenterPositionX - m_nPrvCenterPositionX;
		TranslateY =  m_nCenterPositionY - m_nPrvCenterPositionY;
		m_nCurrenSurfaceOffX += TranslateX;
		m_nCurrenSurfaceOffY += TranslateY;

		//if((m_nCurrenSurfaceOffX> nXBoundary) 
		//	|| (m_nCurrenSurfaceOffX < -nXBoundary)
		//	|| (m_nCurrenSurfaceOffY >nYBoundary)
		//	|| (m_nCurrenSurfaceOffY < -nYBoundary))
		//{
		//	m_TexturePosition.x = float(m_nCenterPositionX / m_nTileWidth) * m_nTileWidth;
		//	m_TexturePosition.y = float(m_nCenterPositionY / m_nTildHeight) * m_nTildHeight;
		//	TranslateX = m_nCenterPositionX - (int)m_TexturePosition.x;
		//	TranslateY = m_nCenterPositionY - (int)m_TexturePosition.y;

		//	m_nCurrenSurfaceOffX= TranslateX;
		//	m_nCurrenSurfaceOffY = TranslateY;

		//	InitVerts();
		//	IMath::BuildIdentityMatrix(m_ModleMatrix);
		//	Matrix4x4 TranlateMatrix;
		//	IMath::BuildIdentityMatrix(TranlateMatrix);
		//	TranlateMatrix.Translate(-TranslateX, -TranslateY, 0);
		//	m_ModleMatrix *= TranlateMatrix;
		//}
		//else
		//{
			Matrix4x4 TranlateMatrix;
			IMath::BuildIdentityMatrix(TranlateMatrix);
			TranlateMatrix.Translate(-TranslateX, -TranslateY, 0);
			m_ModleMatrix *= TranlateMatrix;
			
		//}
	}
	m_nPrvCenterPositionX = m_nCenterPositionX;
	m_nPrvCenterPositionY = m_nCenterPositionY;
	
}

void Level2D_Impl::Render()
{
	m_pShader->SetTexture("u_texture",m_pTexture);

	// set matrix
	IRenderer2D::GetInstance().SetModelViewMatrix(m_ModleMatrix);
	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	int nXTileSize =(m_nHalfSceneWidth / m_nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	int nYTileSize = (m_nHalfSceneHeight / m_nTildHeight) * 2+m_nHalfBuffersize * 2;
	for(int y = 0; y < nYTileSize; y++)
	{	
		for (int x =0; x <nXTileSize; x++)
		{
			int index = y*nXTileSize +x;
			IRenderer2D::GetInstance().DrawRect(&m_pVerts[index * 4], m_pShader);
		}
	}
	
}

void Level2D_Impl::SetCenterPosition(const Vector2& pos)
{
	// TODO:
	m_CenterPosition = pos;
	m_nCenterPositionX = (int)m_CenterPosition.x;
	m_nCenterPositionY = (int)m_CenterPosition.y;
}

const Vector2& Level2D_Impl::GetCenterPosition() const
{
	// TODO: 
	return m_CenterPosition;
}

bool Level2D_Impl::LoadLevel2DFromFile(const char* pszLevel2DFile)
{

	// Parse The MapEditor XML File
	StreamReader* pReader = IFileUtil::GetInstance().LoadFile(pszLevel2DFile);
	if (!pReader) return false;

	TiXmlDocument doc;
	doc.Parse((const char*)pReader->GetBuffer());
	SAFE_RELEASE(pReader);

	if (doc.Error()) return false;
	TiXmlElement* pElemTild = doc.RootElement();


	pElemTild->Attribute("width",&m_nLayerWidth);
	if(m_nLayerWidth <= 0 )return false;
	pElemTild->Attribute("height",&m_nLayerHeight);
	if(m_nLayerHeight<= 0) return false;
	pElemTild->Attribute("tilewidth",&m_nTileWidth);
	if (m_nTileWidth <= 0) return false;
	pElemTild->Attribute("tileheight",&m_nTildHeight);
	if(m_nTildHeight<= 0)return false;
	

	TiXmlElement* LayerSet = pElemTild->FirstChildElement();
	LayerSet = LayerSet->FirstChildElement();
	if(!LayerSet) return false;
	const char* pszTexture = NULL;
	pszTexture = LayerSet->Attribute("source");
	
	if(pszTexture == NULL) return false;

	TiXmlElement* layer = pElemTild->FirstChildElement("layer");
	TiXmlElement* layerData = layer->FirstChildElement("data");
	
	if(!layerData) return false;

	TiXmlElement* Data = layerData->FirstChildElement();
	if(!Data) return false;
	
	SAFE_DELETE_ARRAY(m_pGidAry);
	m_pGidAry = new int[m_nLayerWidth * m_nLayerHeight];
	
	int temp = 0;
	int index = 0;
	while (Data)
	{
		Data->Attribute("gid",&temp);
		m_pGidAry[index] = temp;
		index++;
		Data = Data->NextSiblingElement();
	}
	//Init Shader And TextTrue;
	m_pShader = IShaderMgr::GetInstance().CreateShader("default_shader.xml");
	if(!m_pShader) return false;

	m_pTexture = ITextureMgr::GetInstance().CreateTexture("isometric_tileset.png");
	if(NULL == m_pTexture) return false;
	//Init Render Verts
	SAFE_DELETE_ARRAY(m_pVerts);
	int nXTileSize =(m_nHalfSceneWidth / m_nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	int nYTileSize = (m_nHalfSceneHeight / m_nTildHeight) * 2+m_nHalfBuffersize * 2;
	m_pVerts = new VATTR_POS_UV[nXTileSize * nYTileSize * 4 ];
	InitVerts();
	return true;
}

void Level2D_Impl::InitVerts()
{
	int nXTileSize =(m_nHalfSceneWidth / m_nTileWidth) * 2 + m_nHalfBuffersize * 2;	
	int nYTileSize = (m_nHalfSceneHeight / m_nTildHeight) * 2 + m_nHalfBuffersize * 2;
	//Init Start Coordinate
	float fXstartCoord = -float(nXTileSize / 2) * m_nTileWidth;
	float fYstartCoord =  float(nYTileSize / 2) * m_nTildHeight;
	//TextTrue off 
	float fTextTrueXOff = (float)m_nTileWidth / m_pTexture->GetWidth();
	float fTextTrueYOff = (float)m_nTildHeight/ m_pTexture->GetHeight();

	Vector2 TextTrueCoordinate;
	
	for(int v1=0; v1 < nYTileSize; v1++)
	{
		for ( int v2=0; v2 < nXTileSize; v2++ )
		{
			int noff = v1 * nXTileSize *4 +	v2 * 4;
			Vector2 TextTrueCoordinate;
			TextTrueCoordinate.x = fXstartCoord + m_TexturePosition.x;
			TextTrueCoordinate.y = fYstartCoord + m_TexturePosition.y;
			C2TextTureCoordinate(TextTrueCoordinate);
			m_pVerts[noff].x = fXstartCoord;
			m_pVerts[noff].y = fYstartCoord - m_nTildHeight;
			m_pVerts[noff].z = 0.0f;
			m_pVerts[noff].u = TextTrueCoordinate.x;
			m_pVerts[noff].v = TextTrueCoordinate.y - fTextTrueYOff;

			m_pVerts[noff +1].x = fXstartCoord;
			m_pVerts[noff +1].y = fYstartCoord;
			m_pVerts[noff +1].z = 0.0f;
			m_pVerts[noff +1].u = TextTrueCoordinate.x;
			m_pVerts[noff +1].v = TextTrueCoordinate.y;

			m_pVerts[noff +2].x = fXstartCoord + m_nTileWidth;
			m_pVerts[noff +2].y = fYstartCoord - m_nTildHeight;
			m_pVerts[noff +2].z = 0.0f;
			m_pVerts[noff +2].u = TextTrueCoordinate.x + fTextTrueXOff;
			m_pVerts[noff +2].v = TextTrueCoordinate.y - fTextTrueYOff; 

			m_pVerts[noff +3].x = fXstartCoord + m_nTileWidth;
			m_pVerts[noff +3].y = fYstartCoord;
			m_pVerts[noff +3].z = 0.0f;
			m_pVerts[noff +3].u = TextTrueCoordinate.x + fTextTrueXOff;
			m_pVerts[noff +3].v = TextTrueCoordinate.y;

			//Add  a off distance to iXstarCoord
			fXstartCoord += m_nTileWidth;
			
		}
		//go to next Row, add a off distance to iYstarCoord
		fXstartCoord = - (float)(nXTileSize / 2) * m_nTileWidth;
		fYstartCoord -= m_nTildHeight;
	}
}

Vector2& Level2D_Impl::C2TextTureCoordinate(Vector2& MapPosition)
{
	MapPosition.x += m_nLayerWidth * m_nTileWidth / 2;
    MapPosition.y = m_nLayerHeight * m_nTildHeight/ 2 - MapPosition.y;   
	
	int indexX = (int)MapPosition.x / m_nTileWidth;
	int indexY = (int)MapPosition.y/ m_nTildHeight;
	int index = m_pGidAry[indexY * m_nLayerWidth + indexX];
	
	int nTextTrueXWidth = m_pTexture->GetWidth();
	int  nTextTrueXHeight =m_pTexture->GetHeight();
	
	index--;
	indexX = (index%2) * m_nTildHeight;
	indexY = ((index/2) * m_nTileWidth); 

	MapPosition.x=(float)indexX / nTextTrueXWidth;
	MapPosition.y = 1.0f -(float)indexY/ nTextTrueXHeight;
	return MapPosition;
}
