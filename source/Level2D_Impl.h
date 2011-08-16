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
#include <IShader.h>
#include <IShaderMgr.h>
class Level2D_Impl : public ILevel2D
{
public:
	typedef struct VERTEX_ATTRIBUTE_tag
	{
		float x, y, z;
		float u, v;
	} VERTEX_ATTRIBUTE;
public:
	Level2D_Impl(const char* pszLevel2DFile);
	virtual ~Level2D_Impl();

	virtual void Update(float dt);
	virtual void Render();
	void Terminate();
	virtual void SetCenterPosition(const Vector2& pos);
	virtual const Vector2& GetCenterPosition() const;

public:
	static ILevel2D* CreateLevel2D(const char* pszLevel2DFile);
private:
	bool LoadLevel2DFromFile(const char* pszLevel2DFile);
	inline  Vector2& C2TextTureCoordinate(Vector2& MapPosition );
	void InitVerts();
	
private:
	Vector2 m_CenterPosition;		//当前在地图的位置
	int m_nCenterPositionX;
	int m_nCenterPositionY;
	
	int m_nPrvCenterPositionX;
	int m_nPrvCenterPositionY;

	int m_nCurrenSurfaceOffX;
	int m_nCurrenSurfaceOffY;
	Vector2 m_TexturePosition;		//纹理坐标
	
	int* m_pGidAry;					//存放地图纹理索引
	int m_nLayerWidth;				//地图的宽度
	int m_nLayerHeight;				//地图的高度

	int m_nTileWidth;				//每个Tile的宽度
	int m_nTildHeight;				//每块Tile的高度
		
	int m_nHalfSceneWidth;
	int m_nHalfSceneHeight;

	IShader* m_pShader;			
	ITexture* m_pTexture;
	int m_nHalfBuffersize;
	Matrix4x4 m_ModleMatrix;
	VERTEX_ATTRIBUTE* m_pVerts;		

};
#endif // __LEVEL2D_IMPL_H__
