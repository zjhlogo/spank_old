/*!
 * \file UIRadiaoGroup.cpp
 * \date 2011/09/08 9:52
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIRadioGroup.h>
#include <msg/MsgClick.h>
UIRadioGroup::UIRadioGroup( UIWindow* pParent )
:UIWindow(pParent)
{
	m_unCheckIndex = 0;
	//TODO:
}

UIRadioGroup::~UIRadioGroup()
{
	//TODO:
}

void UIRadioGroup::Render( const RenderParam& param )
{
	//TODO:
	RenderChildrenWindow(param);
}

void UIRadioGroup::Update( float dt )
{
	//TODO:
	UpdateChildrenWindow(dt);
}

bool UIRadioGroup::OnClicked( const Vector2& pos )
{
	//TODO:
	std::vector<UIWindow*> vChild = GetChildRef();
	UIRadio* pTemp;
	for(std::vector<UIWindow*>::iterator it = vChild.begin(); it != vChild.end(); it++ )
	{
		pTemp = dynamic_cast<UIRadio*>(*it);
		if(pTemp->GetID() != m_unCheckIndex)
			pTemp->SetCheckedState(false);
	}
	MsgClick msgclick(MsgClick::CT_CHECK, m_unCheckIndex);
	CallEvent(msgclick);
	return true;
}

bool UIRadioGroup::ProcessTouchEvent( const Vector2& pos, UI_TOUCH_EVENT_TYPE eType )
{
	
	UIWindow* pWindow = FindChildUnderPoint(pos);
	if(pWindow)
	{
		Vector2 localPos = pos - pWindow->GetPosition();
		if(pWindow->ProcessTouchEvent(localPos, eType))
			m_unCheckIndex = pWindow->GetID();
	}	

	bool bProcessed = false;
	switch(eType)
	{
	case UTET_BEGIN:
		{
			bProcessed = OnTouchBegin(pos);
		}
		break;
	case UTET_MOVE:
		{
			bProcessed = OnTouchMove(pos);
		}
		break;
	case UTET_END:
		{
			if (OnTouchEnd(pos)) bProcessed = true;
			if (OnClicked(pos)) bProcessed = true;
		}
		break;
	}
	return bProcessed;
}















