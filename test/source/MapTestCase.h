/*!
 * \file MapTestCase.h
 * \date 27-08-2011 05:30:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MAPTESTCASE_H__
#define __MAPTESTCASE_H__

#include "TestCase.h"
#include <Level2D.h>

class MapTestCase : public TestCase
{
public:
	MapTestCase();
	virtual ~MapTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

private:
	Level2D* m_pLevel;
	Vector2 m_vSpeed;
	Vector2 m_vPosition;

};
#endif // __MAPTESTCASE_H__
