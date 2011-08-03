/*!
 * \file Sprite_Impl.cpp
 * \date 30-07-2011 16:18:48
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Sprite_Impl.h"
#include <IFileMgr.h>
#include <ITextureMgr.h>
#include <IRenderer2D.h>
#include <tinyxml-2.6.2/tinyxml.h>

ISprite* ISprite::CreateSprite(const char* pszSpriteFile)
{
	Sprite_Impl* pSprite = new Sprite_Impl(pszSpriteFile);
	if (!pSprite || !pSprite->IsOK())
	{
		SAFE_DELETE(pSprite);
		return NULL;
	}

	return pSprite;
}

Sprite_Impl::Sprite_Impl(const char* pszSpriteFile)
{
	m_pTexture = NULL;
	m_nNumFrames = 0;
	m_nColumn = 0;
	m_fFrameTime = 0.0f;
	m_nPieceWidth = 0;
	m_nPieceHeight = 0;
	m_nOffsetX = 0;
	m_nOffsetY = 0;
	m_pVerts = NULL;

	m_fCurrTime = 0.0f;
	m_nCurrIndex = 0;
	m_bLoop = true;

	m_bOK = LoadSpriteFromFile(pszSpriteFile);
}

Sprite_Impl::~Sprite_Impl()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE_ARRAY(m_pVerts);
}

void Sprite_Impl::Update(float dt)
{
	m_fCurrTime += dt;
	if (m_fCurrTime > m_fFrameTime)
	{
		m_fCurrTime -= m_fFrameTime;
		m_nCurrIndex = (m_nCurrIndex + 1) % m_nNumFrames;
	}
}

void Sprite_Impl::Render()
{
	IRenderer2D::GetInstance().SetTexture(m_pTexture);
	IRenderer2D::GetInstance().DrawRect(&m_pVerts[m_nCurrIndex*4]);
}

void Sprite_Impl::SetLoop(bool bLoop)
{
	m_bLoop = bLoop;
}

bool Sprite_Impl::LoadSpriteFromFile(const char* pszSpriteFile)
{
	StreamReader* pReader = IFileMgr::GetInstance().LoadFile(pszSpriteFile);
	if (!pReader) return false;

	TiXmlDocument doc;
	doc.Parse((const char*)pReader->GetBuffer());
	SAFE_RELEASE(pReader);

	if (doc.Error()) return false;

	// TODO: parse the xml files
	TiXmlElement* pElmSprite = doc.RootElement();
	if (!pElmSprite) return false;

	const char* pszTexture = NULL;
	pszTexture = pElmSprite->Attribute("texture");
	if (!pszTexture) return false;

	pElmSprite->Attribute("num_pieces", &m_nNumFrames);
	if (m_nNumFrames <= 0) return false;

	pElmSprite->Attribute("column", &m_nColumn);
	if (m_nColumn <= 0) return false;

	int nFrameTime = 0;
	pElmSprite->Attribute("frame_time", &nFrameTime);
	if (nFrameTime <= 0) return false;
	m_fFrameTime = nFrameTime / 1000.0f;

	pElmSprite->Attribute("piece_width", &m_nPieceWidth);
	if (m_nPieceWidth <= 0) return false;

	pElmSprite->Attribute("piece_height", &m_nPieceHeight);
	if (m_nPieceHeight <= 0) return false;

	pElmSprite->Attribute("offset_x", &m_nOffsetX);
	pElmSprite->Attribute("offset_y", &m_nOffsetY);

	m_pTexture = ITextureMgr::GetInstance().CreateTexture(pszTexture);
	if (!m_pTexture) return false;

	CreateVertexs();
	return true;
}

void Sprite_Impl::CreateVertexs()
{
	SAFE_DELETE_ARRAY(m_pVerts);

	m_pVerts = new VERTEX_ATTRIBUTE[m_nNumFrames*4];

	float fHalfWidth = m_nPieceWidth/2.0f;
	float fHalfHeight = m_nPieceHeight/2.0f;

	int nCurrOffsetX = m_nOffsetX;
	int nCurrOffsetY = m_nOffsetY - m_nPieceHeight;

	int nTextureWidth = m_pTexture->GetWidth();
	int nTextureHeight = m_pTexture->GetHeight();

	float fTextureWidth = (float)nTextureWidth;
	float fTextureHeight = (float)nTextureHeight;

	for (int i = 0; i < m_nNumFrames; ++i)
	{
		if (i % m_nColumn == 0)
		{
			nCurrOffsetX = m_nOffsetX;
			nCurrOffsetY += m_nPieceHeight;
		}
		else
		{
			nCurrOffsetX += m_nPieceWidth;
		}

		m_pVerts[i*4+0].x = -fHalfWidth;
		m_pVerts[i*4+0].y = -fHalfHeight;
		m_pVerts[i*4+0].z = 0.0f;
		m_pVerts[i*4+0].u = nCurrOffsetX / fTextureWidth;
		m_pVerts[i*4+0].v = (nTextureHeight - nCurrOffsetY - m_nPieceHeight) / fTextureHeight;

		m_pVerts[i*4+1].x = -fHalfWidth;
		m_pVerts[i*4+1].y = fHalfHeight;
		m_pVerts[i*4+1].z = 0.0f;
		m_pVerts[i*4+1].u = nCurrOffsetX / fTextureWidth;
		m_pVerts[i*4+1].v = (nTextureHeight - nCurrOffsetY) / fTextureHeight;

		m_pVerts[i*4+2].x = fHalfWidth;
		m_pVerts[i*4+2].y = -fHalfHeight;
		m_pVerts[i*4+2].z = 0.0f;
		m_pVerts[i*4+2].u = (nCurrOffsetX+m_nPieceWidth) / fTextureWidth;
		m_pVerts[i*4+2].v = (nTextureHeight - nCurrOffsetY - m_nPieceHeight) / fTextureHeight;

		m_pVerts[i*4+3].x = fHalfWidth;
		m_pVerts[i*4+3].y = fHalfHeight;
		m_pVerts[i*4+3].z = 0.0f;
		m_pVerts[i*4+3].u = (nCurrOffsetX+m_nPieceWidth) / fTextureWidth;
		m_pVerts[i*4+3].v = (nTextureHeight - nCurrOffsetY) / fTextureHeight;
	}
}
