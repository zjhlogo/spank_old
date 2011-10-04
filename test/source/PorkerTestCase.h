/*!
 * \file PorkerTestCase
 * \date 2011/9/20 20:42
 *
 *
 * \author wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __PORKERTESTCASE_H_
#define __PORKERTESTCASE_H_

#include "TestCase.h"
#include <IShader.h>
#include <Tile.h>
#include <INode.h>
#include <ui/uimsg/IMsgBaseUI.h>

class PorkerTestCase : public TestCase
{
public:
	DECLARE_RTTI(PorkerTestCase, TestCase);

	PorkerTestCase();
	virtual ~PorkerTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

	virtual void Render();
	bool OnNormalButtonClick(IMsgBase* pMsg);
	bool OnGrayButtonClick(IMsgBase* pMsg);

private:
	 IShader* m_pShader;	
	 const IMAGE_PIECE* m_pBackGroundImagePiece;
	 Tile* m_pTile;
	 INode* m_pNode;
};

#endif//__PORKERTESTCASE_H_
