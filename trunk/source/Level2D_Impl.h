/*!
 * \file Level2D_Impl.h
 * \date 08-08-2011 22:47:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __LEVEL2D_IMPL_H__
#define __LEVEL2D_IMPL_H__

#include <ILevel2D.h>
#include <ITexture.h>

class Level2D_Impl : public ILevel2D
{
public:
	typedef struct VERTEX_ATTRIBUTE_tag
	{
		float x, y, z;
		float u, v;
	} VERTEX_ATTRIBUTE;
public:
	Level2D_Impl();
	virtual ~Level2D_Impl();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetCenterPosition(const Vector2& pos);
	virtual const Vector2& GetCenterPosition() const;
private:
	bool LoadLevel2DFromFile(const char* pszLevel2DFile);
	void CreateVertexs();

private:
	Vector2 m_CenterPosition;
	
	int* m_GidAry;
	int m_LayerWidth;
	int m_LayerHeight;

	int m_TileWidth;
	int m_TildHeight;
	ITexture* m_pTexture;
	VERTEX_ATTRIBUTE* m_pVerts;
};
#endif // __LEVEL2D_IMPL_H__
