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


int Col,Row,TileWidth,TileHeight,TextTureWidth,TextTureHeight;
int nXTileSize; /*the number instead of every col has how much tiles*/
int nYTileSIze;	/*the number instead of every row has how much tiles*/
FmtL2D::FILE_HEADER_tag FileHeader;
FmtL2D::TILE_INFO* TILEINFO = NULL;
uint *m_pGidAry= NULL;

template<class out_type,class in_value>
out_type translate(const in_value & t)
{
	stringstream stream;
	stream<<t;
	out_type result;
	stream>>result;
	return result;
}
void ShowTheFileHeaderInfo(FmtL2D::FILE_HEADER& FileHeader)
{
	cout<<FileHeader.nMagicNumber<<endl;
	cout<<FileHeader.nVersionNumber<<endl;
	cout<<FileHeader.nMapCol<<endl;
	cout<<FileHeader.nMapRow<<endl;
	cout<<FileHeader.nDefaultTile<<endl;
	cout<<FileHeader.nNumTiles<<endl;
	cout<<FileHeader.nTileHeight<<endl;
	cout<<FileHeader.nTileWidth<<endl;
	cout<<FileHeader.szTextureFile<<endl;
}
void CreatL2DFile()
{
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
}
bool ParseLevel2DXmlFile(char* pszXmlFileName, uint nDefaultTile)
{
	
	cout<<"Parse the"<<pszXmlFileName<<" Map XML File."<<endl;
	TiXmlDocument doc(pszXmlFileName);
	doc.LoadFile();
	if(doc.Error()) 
		
	{
		cout<<"Parse the Xml file failed"<<endl;
		return false;
	}
	//Pares The FileHeader information
	
	FileHeader.nMagicNumber = FmtL2D::MAGIC_NUMBER;
	FileHeader.nVersionNumber = FmtL2D::VERSION_NUMBER;

	TiXmlElement* pElemTild = doc.RootElement();

	
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
	if(NULL == pszTexture) return false;
	LayerSet->Attribute("width",&TextTureWidth);
	if(TextTureWidth <= 0) return false;
	LayerSet->Attribute("height",&TextTureHeight);
	if(TextTureHeight <= 0) return false;
	FileHeader.nNumTiles = (TextTureWidth / TileWidth )* (TextTureHeight/TileHeight);

	string PathFileName(pszTexture);
	int Position = PathFileName.find_last_of('/');
	Position++;
	string FileName;
	FileName.assign(&PathFileName[Position],PathFileName.size() - Position);
	strcpy(FileHeader.szTextureFile,FileName.c_str());
	FileHeader.nDefaultTile = nDefaultTile;
	
	//Check The  the Parsed FILE_HEADER_tag information
	ShowTheFileHeaderInfo(FileHeader);
	
	TiXmlElement* layer = pElemTild->FirstChildElement("layer");
	TiXmlElement* layerData = layer->FirstChildElement("data");
	if(!layerData) return false;
	TiXmlElement* Data = layerData->FirstChildElement();
	if(!Data) return false;
	//Calculation  every texture size
	 nXTileSize = (TextTureWidth / TileWidth );
	 nYTileSIze = (TextTureHeight/TileHeight);
	//Calculation  every texture off size
	float TextTureOffX = (float)TileWidth / TextTureWidth;
	float TextTureOffY = (float)TileHeight/ TextTureHeight;
	
	TILEINFO = new FmtL2D::TILE_INFO[nXTileSize * nYTileSIze];
	//Calculation every texture tile coordinate 
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
	//parse the Layer Data
	m_pGidAry = new uint[Col *Row];
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
	//Create L2D file
	CreatL2DFile();
	
	return true;
}

int main(int agrc, char** argv)
{
	char* XMLFILE =NULL;
	uint nDefaultTile = 0;
	if(agrc<=1)
	{
		cout<<"Error,can't find the file name"<<endl;
		XMLFILE = "test.xml";
	}
	if(3 <= agrc)
	{
		XMLFILE = argv[1];
		nDefaultTile = translate<int>(argv[2]);
	}
	ParseLevel2DXmlFile(XMLFILE,nDefaultTile);
	system("pause");
	
}
