/*!
 * \file Sprite.h
 * \date 30-07-2011 16:18:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "IRenderableObject.h"
#include "BaseTypeEx.h"
#include "IShader.h"
#include "INode.h"

class Sprite : public IRenderableObject
{
public:
	DECLARE_RTTI(Sprite, IRenderableObject);

	Sprite(const char* pszSpriteFile);
	virtual ~Sprite();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetLoop(bool bLoop);

private:
	bool LoadSpriteFromFile(const char* pszSpriteFile);
	void CreateVertexs();
	INode* GetParentNode();

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
	QUAD_VERT_POS_UV* m_pQuadVerts;

	float m_fCurrTime;
	int m_nCurrIndex;
	bool m_bLoop;

};
#endif // __SPRITE_H__
