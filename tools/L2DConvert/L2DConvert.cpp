/*!
 * \file L2DConvert.cpp
 * \date 27-08-2011 10:59:03
 * 
 * 
 * \author 
 */
#include "L2DConvert.h"
#include <string>
#include <iostream>

L2DConvert::L2DConvert()
{
	m_nTextureHeight = 0;
	m_nTextureWidth = 0;
	m_pGridArray = NULL;
	m_pTileInfo = NULL;
}

L2DConvert::~L2DConvert()
{
	SAFE_DELETE_ARRAY(m_pGridArray);
	SAFE_DELETE_ARRAY(m_pTileInfo);
}

L2DConvert& L2DConvert::GetInstance()
{
	static L2DConvert ObjL2D;
	return ObjL2D;
}

bool L2DConvert::ParseXmlFile(const char* pszFileName)
{
	TiXmlDocument doc(pszFileName);
	doc.LoadFile();
	if(doc.Error()) return false;

	TiXmlElement* pElemTile = doc.RootElement();
	int nTempValue = 0;

	pElemTile->Attribute("width", &nTempValue);
	if(nTempValue <= 0 ) return false;
	m_FileHeader.nMapCol = nTempValue;

	nTempValue = 0;
	pElemTile->Attribute("height", &nTempValue);
	if(nTempValue<= 0) return false;
	m_FileHeader.nMapRow = nTempValue;

	nTempValue = 0;
	pElemTile->Attribute("tilewidth", &nTempValue);
	if (nTempValue <= 0) return false;
	m_FileHeader.nTileWidth = nTempValue;

	nTempValue = 0;
	pElemTile->Attribute("tileheight", &nTempValue);
	if(nTempValue <= 0)return false;
	m_FileHeader.nTileHeight = nTempValue;

	TiXmlElement* LayerSet = pElemTile->FirstChildElement();
	LayerSet = LayerSet->FirstChildElement();
	if(!LayerSet) return false;
	
	nTempValue = 0;
	LayerSet->Attribute("width", &nTempValue);
	if(nTempValue <= 0) return false;
	m_nTextureWidth = nTempValue;

	nTempValue = 0;
	LayerSet->Attribute("height", &nTempValue);
	m_nTextureHeight = nTempValue;

	nTempValue = 0;
	const char* pszTexture = NULL;
	pszTexture = LayerSet->Attribute("source");
	if(NULL == pszTexture) return false;
	std::string strPathFileName(pszTexture);

	int nPosition = strPathFileName.find_last_of('/')+1;

	std::string strFileName;
	strFileName.assign(&strPathFileName[nPosition], strPathFileName.size() - nPosition);
	strncpy_s(m_FileHeader.szTextureFile, strFileName.c_str(), FmtL2D::FILE_NAME_LENGTH);
	m_FileHeader.szTextureFile[FmtL2D::FILE_NAME_LENGTH - 1] = '\0';

	TiXmlElement* pElmLayer = pElemTile->FirstChildElement("layer");
	TiXmlElement* pElmLayerData = pElmLayer->FirstChildElement("data");
	if(!pElmLayerData) return false;

	TiXmlElement* pElmData = pElmLayerData->FirstChildElement();
	if(!pElmData) return false;

	m_pGridArray = new uint[m_FileHeader.nMapCol * m_FileHeader.nMapRow];
	int nIndex = 0;
	while (pElmData)
	{
		nTempValue = 0;
		pElmData->Attribute("gid", &nTempValue);
		m_pGridArray[nIndex++] = nTempValue - 1;	

		pElmData = pElmData->NextSiblingElement();
	}

	return true;
}

void L2DConvert::ConverToL2D(uint nDefaultTile)
{
	m_FileHeader.nMagicNumber = FmtL2D::MAGIC_NUMBER;
	m_FileHeader.nVersionNumber = FmtL2D::VERSION_NUMBER;
	m_FileHeader.nDefaultTile = nDefaultTile;
	
	uint unTextureColTileNum = m_nTextureWidth / m_FileHeader.nTileWidth;
	uint unTextureRowTileNum = m_nTextureHeight / m_FileHeader.nTileHeight;
	m_FileHeader.nNumTiles = unTextureColTileNum * unTextureRowTileNum;

	float fTextureDu = (float)m_FileHeader.nTileWidth / m_nTextureWidth; 
	float fTextureDv = (float)m_FileHeader.nTileHeight / m_nTextureHeight;
	m_pTileInfo = new FmtL2D::TILE_INFO[m_FileHeader.nNumTiles];

	for (uint y = 0; y < unTextureRowTileNum; ++y)
	{
		for (uint x = 0; x < unTextureColTileNum; ++x)
		{
			m_pTileInfo[y*unTextureColTileNum+x].u = float(x * m_FileHeader.nTileWidth) / m_nTextureWidth;
			m_pTileInfo[y*unTextureColTileNum+x].v =  1.0f - float(y*m_FileHeader.nTileHeight + m_FileHeader.nTileHeight) / m_nTextureHeight;
			m_pTileInfo[y*unTextureColTileNum+x].du = fTextureDu;
			m_pTileInfo[y*unTextureColTileNum+x].dv = fTextureDv;
		}
	}
}

bool L2DConvert::CreateL2DFile(const char* pszXMlFileName, uint nDefaultTile, const char* pszL2DFileName)
{
	if(NULL == pszL2DFileName) return false;
	if(!ParseXmlFile(pszXMlFileName)) return false;
	ConverToL2D(nDefaultTile);

	FILE* pFile = NULL;
	fopen_s(&pFile, pszL2DFileName, "wb");

	if (!pFile)
	{
		std::cout << "Create L2D file failed" << std::endl;
		return false;
	}

	fwrite(&m_FileHeader, sizeof(m_FileHeader), 1, pFile);
	fwrite(m_pTileInfo, sizeof(FmtL2D::TILE_INFO), m_FileHeader.nNumTiles, pFile);
	fwrite(m_pGridArray, sizeof(uint), m_FileHeader.nMapCol * m_FileHeader.nMapRow, pFile);
	fclose(pFile);

	std::cout << "Create L2D file success" << std::endl;
	return true;
}
