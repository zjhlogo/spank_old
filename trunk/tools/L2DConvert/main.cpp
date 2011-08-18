/*!
 * \file main.cpp
 * \date 16-08-2011 20:28:08
 * 
 * 
 * \author ??
 */
#include <iostream>
#include <fileformat/FmtL2D.h>
#include <tinyxml.h>
#include <math/IMath.h>
#include <fstream>
#include <sstream>
#include <Windows.h>
using namespace std;


int main(int agrc, char** argv)
{
	char* XMLFILE =NULL;
	if(agrc<=1)
	{
		cout<<"Error,can't find the file name"<<endl;
		XMLFILE = "test.xml";
	}
	else
	{
		XMLFILE = argv[1];
	}
	cout<<"Parse the"<<XMLFILE<<" Map XML File."<<endl;
	TiXmlDocument doc(XMLFILE);
	doc.LoadFile();
	if(doc.Error()) 
		cout<<"Parse the Xml file faild"<<endl;
	//Pares The FileHeader INFO
	FmtL2D::FILE_HEADER_tag FileHeader;
	FileHeader.nMagicNumber = FmtL2D::MAGIC_NUMBER;
	FileHeader.nVersionNumber = FmtL2D::VERSION_NUMBER;
	
	TiXmlElement* pElemTild = doc.RootElement();

	int Col,Row,TileWidth,TileHeight,TextTureWidth,TextTureHeight;
	pElemTild->Attribute("width",&Col);
	if(Col <= 0 )return false;
	pElemTild->Attribute("height",&Row);
	if(Row<= 0) return false;
	pElemTild->Attribute("tilewidth",&TileWidth);
	if (TileWidth <= 0) return false;
	pElemTild->Attribute("tileheight",&TileHeight);
	if(TileHeight<= 0)return false;

	FileHeader.nMapCol =Col;
	FileHeader.nMapRow =Row;
	FileHeader.nTileHeight = TileHeight;
	FileHeader.nTileWidth = TileWidth;
	
	TiXmlElement* LayerSet = pElemTild->FirstChildElement();
	LayerSet = LayerSet->FirstChildElement();
	if(!LayerSet) return false;
	const char* pszTexture = NULL;
	pszTexture = LayerSet->Attribute("source");
	LayerSet->Attribute("width",&TextTureWidth);
	LayerSet->Attribute("height",&TextTureHeight);
	FileHeader.nNumTiles = (TextTureWidth / TileWidth )* (TextTureHeight/TileHeight);
	string PathFileName(pszTexture);
	int Position = PathFileName.find_last_of('/');
	Position++;
	string FileName;
	FileName.assign(&PathFileName[Position],PathFileName.size() - Position);
	strcpy(FileHeader.szTextureFile,FileName.c_str());

	//////////////////////////////////////////////////////////////////////////
	//Check The FILE_HEADER_tag INFO
	cout<<FileHeader.nMagicNumber<<endl;
	cout<<FileHeader.nVersionNumber<<endl;
	cout<<FileHeader.nMapCol<<endl;
	cout<<FileHeader.nMapRow<<endl;
	cout<<FileHeader.nNumTiles<<endl;
	cout<<FileHeader.nTileHeight<<endl;
	cout<<FileHeader.nTileWidth<<endl;
	cout<<FileHeader.szTextureFile<<endl;
	//
	//////////////////////////////////////////////////////////////////////////
	TiXmlElement* layer = pElemTild->FirstChildElement("layer");
	TiXmlElement* layerData = layer->FirstChildElement("data");
	if(!layerData) return false;
	TiXmlElement* Data = layerData->FirstChildElement();
	if(!Data) return false;
	//纹理的Tile的大小
	int nXTileSize = (TextTureWidth / TileWidth );
	int nYTileSIze = (TextTureHeight/TileHeight);
	//每块纹理的偏移量
	float TextTureOffX = (float)TileWidth / TextTureWidth;
	float TextTureOffY = (float)TileHeight/ TextTureHeight;

	FmtL2D::TILE_INFO* TILEINFO = new FmtL2D::TILE_INFO[nXTileSize * nYTileSIze];
	for (int y = 0; y < TextTureHeight/TileHeight; y++)
	{
		for (int x = 0;x<(TextTureHeight/TileHeight); x++ )
		{
			TILEINFO[y *nXTileSize + x ].u = float(x*TileWidth) / TextTureWidth;
			TILEINFO[y *nXTileSize + x ].v =  1.0f - float(y*TileHeight + TileHeight) /TextTureHeight;
			TILEINFO[y *nXTileSize + x ].du = TextTureOffX;
			TILEINFO[y *nXTileSize + x ].dv = TextTureOffY;
		}
	}
	uint *m_pGidAry = new uint[Col *Row];
	int temp = 0;
	int index = 0;
	int nTextTureXsize = TextTureWidth / TileWidth;
	while (Data)
	{
		Data->Attribute("gid",&temp);
		temp--;
		m_pGidAry[index] = temp;	
		index++;
		Data = Data->NextSiblingElement();
	}
	//////////////////////////////////////////////////////////////////////////
	// Create L2D FIle
	ofstream binary_file;
	char Pathbuffer[256];
	GetCurrentDirectory(256,Pathbuffer);
	string L2DFileName(Pathbuffer);
	L2DFileName.append("\\OUT.L2D");
	cout<<L2DFileName.c_str()<<endl;
	binary_file.open(L2DFileName.c_str(),ios::out|ios::binary);
	if(!binary_file)
		cout<<"Open L2D file failed"<<endl;
	else
		cout<<"Open L2D file success"<<endl;

	binary_file.write((char*)&FileHeader,sizeof(FmtL2D::FILE_HEADER_tag));
	cout<<sizeof(FmtL2D::FILE_HEADER);
	binary_file.write((char*)TILEINFO, sizeof(FmtL2D::TILE_INFO_tag) * nXTileSize * nYTileSIze);
	binary_file.write((char*)m_pGidAry,sizeof(uint)* Col * Row);
	binary_file.close();
	
	SAFE_DELETE_ARRAY(m_pGidAry);
	SAFE_DELETE_ARRAY(TILEINFO);
	system("pause");
}
