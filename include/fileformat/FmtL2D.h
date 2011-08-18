/*!
 * \file FmtL2D.h
 * \date 8-16-2011 17:43:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __FMTL2D_H__
#define __FMTL2D_H__
#include "../include/BaseType.h"
class FmtL2D
{
public:
	enum CONST_DEFINE
	{
		MAGIC_NUMBER = 0x0044324C,		/*!< "L2D" */
		VERSION_NUMBER = 100,			/*!< version 1.0.0 */
		FILE_NAME_LENGTH = 64,
	};

	/*! first, comes the file header */
	typedef struct FILE_HEADER_tag
	{
		uint nMagicNumber;				/*!< always = MAGIC_NUMBER */
		uint nVersionNumber;			/*!< always = VERSION_NUMBER */

		uint nMapRow;					/*!< row of tile on the map */
		uint nMapCol;					/*!< col of tile on the map */

		uint nNumTiles;					/*!< number of tiles on the texture */
		uint nTileWidth;				/*!< tile width on the texture */
		uint nTileHeight;				/*!< tile height on the texture */
		char szTextureFile[FILE_NAME_LENGTH];	/*!< tile texture file */
	} FILE_HEADER;

	/*! second, comes the FILE_HEADER::nNumTiles of TILE_INFO */
	typedef struct TILE_INFO_tag
	{
		float u, v;						/*!< tile u, v */
		float du, dv;					/*!< tile width, height scaled into (0 ~ 1) */
	} TILE_INFO;

	/*! third, comes the FILE_HEADER::nMapRow*FILE_HEADER::nMapCol of index (uint)
	 *
	 * uint tileIndex[nMapRow*nMapCol];
	 */
};
#endif // __FMTL2D_H__
