/*!
 * \file Sprite_Impl.h
 * \date 30-07-2011 16:18:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SPRITE_IMPL_H__
#define __SPRITE_IMPL_H__

#include <ISprite.h>
#include <IShader.h>

class Sprite_Impl : public ISprite
{
public:
	typedef struct VERTEX_ATTRIBUTE_tag
	{
		float x, y, z;
		float u, v;
	} VERTEX_ATTRIBUTE;

public:
	Sprite_Impl(const char* pszSpriteFile);
	virtual ~Sprite_Impl();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetLoop(bool bLoop);

private:
	bool LoadSpriteFromFile(const char* pszSpriteFile);
	void CreateVertexs();

private:
	IShader* m_pShader;
	ITexture* m_pTexture;
	int m_nNumFrames;
	int m_nColumn;
	float m_fFrameTime;
	int m_nPieceWidth;
	int m_nPieceHeight;
	int m_nOffsetX;
	int m_nOffsetY;
	VERTEX_ATTRIBUTE* m_pVerts;

	float m_fCurrTime;
	int m_nCurrIndex;
	bool m_bLoop;

};
#endif // __SPRITE_IMPL_H__
