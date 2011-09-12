/*!
 * \file ResourceMgr_Impl.h
 * \date 12-09-2011 16:42:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RESOURCEMGR_IMPL_H__
#define __RESOURCEMGR_IMPL_H__

#include <IResourceMgr.h>
#include <string>
#include <vector>

class ResourceMgr_Impl : public IResourceMgr
{
public:
	typedef std::map<int, ITexture*> TM_TEXTURE_INFO;
	typedef std::map<std::string, TEXTURE_PIECE> TM_TEXTURE_PIECE;
	typedef std::vector<ITexture*> TV_TEXTURE;

public:
	ResourceMgr_Impl();
	virtual ~ResourceMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual bool AddTexturePieceList(const char* pszFile);
	virtual const TEXTURE_PIECE* FindTexturePiece(const char* pszName);

private:
	ITexture* FindTexture(TM_TEXTURE_INFO textureInfoMap, int nID);

private:
	TM_TEXTURE_PIECE m_TexturePieceMap;
	TV_TEXTURE m_vTextures;

};
#endif // __RESOURCEMGR_IMPL_H__
