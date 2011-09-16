/*!
 * \file TweenActionMove.cpp
 * \date 2011/09/16 14:33
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ICore.h>
#include <action/ActionSequeue.h>
#include <action/ActionLoop.h>
#include <action/ActionQuadraticMove.h>
#include <action/ActionBackMove.h>
#include "TweentActionMove.h"
TweenActionMove::TweenActionMove()
:TestCase("TweenAction")
{	
	m_pSpriteAction = NULL;
	m_pActionNode = NULL;
}
TweenActionMove::~TweenActionMove()
{

}


bool TweenActionMove::Initialize( UIScreen* pUIScreen )
{
	m_pSpriteAction = new Sprite("test_sprite.xml");
	if (!m_pSpriteAction) return true;

	m_pActionNode = ICore::GetInstance().GetRootNode()->CreateChildNode();
	m_pActionNode->AttachObject(m_pSpriteAction);

	ActionSequeue* pActionFregment = new ActionSequeue();

	pActionFregment->AddAction(new ActionBackMove(MOVE_BACK_EASEINOUT,Vector3(-200.0f, 0.0f, 0.0f), Vector3(200.0f, 0.0f, 0.0f), 3.0f));
	ActionSequeue* pActionSequeue = new ActionSequeue();
	pActionSequeue->AddAction(pActionFregment);

	ActionLoop * pActionLoop = new ActionLoop(pActionSequeue);
	m_pActionNode->RunAction(pActionLoop);
	return true;
}


void TweenActionMove::Terminate()
{
	ICore::GetInstance().GetRootNode()->RemoveChildNode(m_pActionNode);
	m_pActionNode = NULL;
	SAFE_DELETE(m_pSpriteAction);
}

