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
#include <BaseTypeEx.h>
#include <fileformat/fmtl2d.h>
class Level2D_Impl : public ILevel2D
{
public:
	Level2D_Impl(const char* pszLevel2DFile);
	virtual ~Level2D_Impl();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetCenterPosition(const Vector2& pos);
	virtual const Vector2& GetCenterPosition() const;

	static ILevel2D* CreateLevel2D(const char* pszLevel2DFile);

private:

	bool LoadLevel2DFromFile(const char* pszLevel2DFile);
	bool C2TextTureCoordinate(Vector2& MapPosition, uint& index);
	void InitVerts();
	void UpdateVerts();
	
private:
	Vector2 m_CenterPosition;		//Current Map Coordinate
	Vector2 m_PrvCenterPosition;	//previous Map Coordinate
	
	int m_nHalfSceneWidth;
	int m_nHalfSceneHeight;
	int m_nHalfBuffersize;			//In the Construct function set the HalfBuffersize
	
	IShader* m_pShader;				
	ITexture* m_pTexture;			//The Map used TextTure
	Matrix4x4 m_ModelMatrix;
	VATTR_POS_UV* m_pVerts;		
	
	FmtL2D::FILE_HEADER m_FILEHEADER;
	FmtL2D::TILE_INFO* m_TILEINFO;
	uint* m_pGidAry;
	bool* m_pMapFlag;
};
#endif // __LEVEL2D_IMPL_H__
