/*!
 * \file L2DConvert.h
 * \date 27-08-2011 10:58:51
 * 
 * 
 * \author 
 */
#ifndef  __L2DCONVERT_H_
#define  __L2DCONVERT_H_

#include <fileformat/FmtL2D.h>
#include <tinyxml.h>

class L2DConvert
{
public:
	L2DConvert();
	~L2DConvert();

	static L2DConvert& GetInstance();
	bool CreateL2DFile(const char* pszXMlFileName, uint nDefaultTile, const char* pszL2DFileName);

private:
	void ConverToL2D(uint unDefaultTile);
	bool ParseXmlFile(const char* pszFileName);

private:
	uint m_nTextureWidth;
	uint m_nTextureHeight;

	FmtL2D::FILE_HEADER m_FileHeader;
	FmtL2D::TILE_INFO* m_pTileInfo;
	uint* m_pGridArray;

};
#endif//__L2DCONVERT_H_
