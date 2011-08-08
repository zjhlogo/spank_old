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

class Level2D_Impl : public ILevel2D
{
public:
	Level2D_Impl();
	virtual ~Level2D_Impl();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetCenterPosition(const Vector2& pos);
	virtual const Vector2& GetCenterPosition() const;

};
#endif // __LEVEL2D_IMPL_H__
