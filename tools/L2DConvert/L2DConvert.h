#ifndef  __L2DCONVERT_H_
#define  __L2DCONVERT_H_
#include <fileformat/FmtL2D.h>
#include <tinyxml.h>
#include <math/IMath.h>

class L2DConvert
{
public:
	L2DConvert();
	~L2DConvert(void);
public:
	static L2DConvert& GetInstance();
	bool CreateL2DFile(char* pszXMlFileName,uint unDefaultTile,char* pszL2DFileName);
private:
	void ConverToL2D(uint unDefaultTile);
	bool ParseXmlFile(char* pszFileName);
private:
	uint m_unTextureWidth;
	uint m_unTextureHeight;
	FmtL2D::FILE_HEADER m_FileHeader;
	FmtL2D::TILE_INFO* m_pTileInfo;
	uint* m_pGidAry;
};
#endif//__L2DCONVERT_H_