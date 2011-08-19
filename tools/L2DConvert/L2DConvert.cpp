#include <util/IFileUtil.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "L2DConvert.h"
using namespace std;
L2DConvert::L2DConvert()
{
	//TODO:
	m_pGidAry = NULL;
	m_pTileInfo = NULL;
	m_unTextureHeight = 0;
	m_unTextureWidth = 0;
}

L2DConvert::~L2DConvert(void)
{
	//TODO:
	SAFE_DELETE_ARRAY(m_pGidAry);
	SAFE_DELETE_ARRAY(m_pTileInfo);
}
L2DConvert& L2DConvert::GetInstance()
{
	static L2DConvert ObjL2D;
	return ObjL2D;
}

bool L2DConvert::ParseXmlFile(char* pszFileName)
{
	//TODO:
	
	TiXmlDocument doc(pszFileName);
	doc.LoadFile();
	if(doc.Error()) 
		return false;
	TiXmlElement* pElemTild = doc.RootElement();

	int unTempValue = 0;

	pElemTild->Attribute("width", &unTempValue);
	if(unTempValue <= 0 )return false;
	m_FileHeader.nMapCol = unTempValue;
	unTempValue = 0;
	pElemTild->Attribute("height", &unTempValue);
	if(unTempValue<= 0) return false;
	m_FileHeader.nMapRow = unTempValue;
	unTempValue = 0;
	pElemTild->Attribute("tilewidth", &unTempValue);
	if (unTempValue <= 0) return false;
	m_FileHeader.nTileWidth = unTempValue;
	unTempValue = 0;
	pElemTild->Attribute("tileheight", &unTempValue);
	if(unTempValue <= 0)return false;
	m_FileHeader.nTileHeight = unTempValue;
	unTempValue = 0;
	
	TiXmlElement* LayerSet = pElemTild->FirstChildElement();
	LayerSet = LayerSet->FirstChildElement();
	if(!LayerSet) return false;
	
	LayerSet->Attribute("width", &unTempValue);
	if(unTempValue <= 0) return false;
	m_unTextureWidth = unTempValue;
	unTempValue = 0;
	LayerSet->Attribute("height", &unTempValue);
	m_unTextureHeight = unTempValue;
	unTempValue = 0;

	const char* pszTexture = NULL;
	pszTexture = LayerSet->Attribute("source");
	if(NULL == pszTexture) return false;
	string PathFileName(pszTexture);
	int Position = PathFileName.find_last_of('/');
	Position++;
	string FileName;
	FileName.assign(&PathFileName[Position], PathFileName.size() - Position);
	strcpy(m_FileHeader.szTextureFile,FileName.c_str());
	pszTexture = NULL;

	TiXmlElement* layer = pElemTild->FirstChildElement("layer");
	TiXmlElement* layerData = layer->FirstChildElement("data");
	if(!layerData) return false;
	TiXmlElement* Data = layerData->FirstChildElement();
	if(!Data) return false;
	m_pGidAry = new uint[m_FileHeader.nMapCol * m_FileHeader.nMapRow];
	int index = 0;
	while (Data)
	{
		Data->Attribute("gid", &unTempValue);
		unTempValue--;
		m_pGidAry[index] = unTempValue;	
		index++;
		Data = Data->NextSiblingElement();
	}
	return true;
}

void L2DConvert::ConverToL2D(uint unDefaultTile)
{
	//TODO:
	m_FileHeader.nMagicNumber = FmtL2D::MAGIC_NUMBER;
	m_FileHeader.nVersionNumber = FmtL2D::VERSION_NUMBER;
	m_FileHeader.nDefaultTile = unDefaultTile;
	
	uint unTextureColTileNum = m_unTextureWidth / m_FileHeader.nTileWidth;
	uint unTextureRowTileNum = m_unTextureHeight / m_FileHeader.nTileHeight;
	m_FileHeader.nNumTiles = unTextureColTileNum * unTextureRowTileNum;

	float fTextureDu = (float)m_FileHeader.nTileWidth / m_unTextureWidth; 
	float fTextureDv = (float)m_FileHeader.nTileHeight / m_unTextureHeight;
	m_pTileInfo = new FmtL2D::TILE_INFO[unTextureColTileNum * unTextureRowTileNum];

	for (uint y = 0; y < unTextureRowTileNum; ++y)
	{
		for (uint x = 0;x<unTextureColTileNum; ++x)
		{
			m_pTileInfo[y *unTextureColTileNum + x ].u = float(x * m_FileHeader.nTileWidth) / m_unTextureWidth;
			m_pTileInfo[y *unTextureColTileNum + x ].v =  1.0f - float(y*m_FileHeader.nTileHeight + m_FileHeader.nTileHeight) / m_unTextureHeight;
			m_pTileInfo[y *unTextureColTileNum + x ].du = fTextureDu;
			m_pTileInfo[y *unTextureColTileNum + x ].dv = fTextureDv;
		}
	}
	
}
bool L2DConvert::CreateL2DFile(char *pszXMlFileName, uint unDefaultTile, char *pszL2DFileName)
{
	if(NULL == pszL2DFileName)
		return false;
	if(!ParseXmlFile(pszXMlFileName))
		return false;
	ConverToL2D(unDefaultTile);

	ofstream binary_file;
	binary_file.open(pszL2DFileName,ios::out|ios::binary);
	if(!binary_file)
	{
		cout<<"Create L2D file failed"<<endl;
		return false;
	}
	else
	{
		cout<<"Create L2D file success"<<endl;
	}
	binary_file.write((char*)&m_FileHeader,sizeof(FmtL2D::FILE_HEADER_tag));
	binary_file.write((char*)m_pTileInfo, sizeof(FmtL2D::TILE_INFO_tag) * (m_unTextureHeight / m_FileHeader.nTileHeight) * (m_unTextureWidth / m_FileHeader.nTileWidth ));
	binary_file.write((char*)m_pGidAry,sizeof(uint) * m_FileHeader.nMapCol * m_FileHeader.nMapRow);
	binary_file.close();
	return true;
}
