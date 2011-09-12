/*!
 * \file IResourceMgr.h
 * \date 12-09-2011 16:42:59
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRESOURCEMGR_H__
#define __IRESOURCEMGR_H__

#include "IMgr.h"
#include "BaseTypeEx.h"

class IResourceMgr : public IMgr
{
public:
	static IResourceMgr& GetInstance();

	virtual bool AddTexturePieceList(const char* pszFile) = 0;
	virtual const TEXTURE_PIECE* FindTexturePiece(const char* pszName) = 0;

};
#endif // __IRESOURCEMGR_H__
