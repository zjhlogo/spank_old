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
#include <ITextureMgr.h>
#include <IRenderer2D.h>
#include <tinyxml-2.6.2/tinyxml.h>
Level2D_Impl::Level2D_Impl()
{
	// TODO:
	m_CenterPosition.x = 0;
	m_CenterPosition.y = 0;
	
	m_GidAry = NULL;
	m_LayerWidth = 0;
	m_LayerHeight = 0;
	
	m_TileWidth = 0;
	m_TildHeight = 0;
	m_pTexture = NULL;
	m_pVerts = NULL;
}

Level2D_Impl::~Level2D_Impl()
{
	// TODO: 
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE_ARRAY(m_GidAry);
	SAFE_DELETE_ARRAY(m_pVerts);
}

void Level2D_Impl::Update(float dt)
{
	// TODO: 
}

void Level2D_Impl::Render()
{
	// TODO: 
	CreateVertexs();
	
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
	//TODO:
	StreamReader* pReader = IFileUtil::GetInstance().LoadFile(pszLevel2DFile);
	if (!pReader) return false;

	TiXmlDocument doc;
	TiXmlElement* pElemTild = doc.RootElement();


	pElemTild->Attribute("width",&m_LayerWidth);
	if(m_LayerWidth <= 0 )return false;
	pElemTild->Attribute("height",&m_LayerHeight);
	if(m_LayerHeight<= 0) return false;
	pElemTild->Attribute("tilewidth",&m_TileWidth);
	if (m_TileWidth <= 0) return false;
	pElemTild->Attribute("tileheight",&m_TildHeight);
	if(m_TildHeight<= 0)return false;

	TiXmlElement* LayerSet = pElemTild->FirstChildElement();
	LayerSet = LayerSet->FirstChildElement();
	if(!LayerSet) return false;
	const char* pszTexture = NULL;
	pszTexture = LayerSet->Attribute("source");
	
	if(pszTexture == NULL) return false;
	//load Min texture
	m_pTexture = ITextureMgr::GetInstance().CreateTexture(pszTexture);
	
	TiXmlElement* layer = pElemTild->FirstChildElement("layer");
	TiXmlElement* layerData = layer->FirstChildElement("data");
	
	if(!layerData) return false;

	TiXmlElement* Data = layerData->FirstChildElement();
	if(!Data) return false;
	
	SAFE_DELETE_ARRAY(m_GidAry);
	m_GidAry = new int[m_LayerWidth * m_LayerHeight];
	
	int temp = 0;
	int index = 0;
	do 
	{
		Data->Attribute("gid",&temp);
		//µØÍ¼ÎÆÀí¿éË÷Òý
		m_GidAry[index] = temp;
		index++;
		Data = Data->NextSiblingElement();
	} while (Data);

	return true;

}
void Level2D_Impl::CreateVertexs()
{
	//TODO:
	SAFE_DELETE_ARRAY(m_pVerts);
	int ScenWidth = 800;
	int ScenHeight = 480;

	int Xsize = ScenWidth / m_TileWidth;
	int Ysize = ScenHeight / m_TildHeight;
	m_pVerts = new VERTEX_ATTRIBUTE[Ysize * Xsize * 4*4];
	
}
