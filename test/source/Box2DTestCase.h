/*!
 * \file Box2DTestCase.h
 * \date 8-30-2011 16:21:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BOX2DTESTCASE_H__
#define __BOX2DTESTCASE_H__

#include "TestCase.h"
#include <IShader.h>
#include <Box2D_v2.1.2/Box2D/Box2D.h>

class Box2DTestCase : public TestCase
{
public:
	Box2DTestCase();
	virtual ~Box2DTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

private:
	b2World* m_pWorld;
	b2Body* m_pBody;
	IShader* m_pShader;

};
#endif // __BOX2DTESTCASE_H__
