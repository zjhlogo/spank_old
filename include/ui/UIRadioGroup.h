/*!
 * \file UIRadioGroup.h
 * \date 2011/09/08 9:52
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __UIRADIOGROUP_H_
#define __UIRADIOGROUP_H_

#include <ui/UIWindow.h>
#include <ui/UIRadio.h>
#include <vector>
class UIRadioGroup : public UIWindow
{
public:
	UIRadioGroup(UIWindow* pParent);
	virtual ~UIRadioGroup();

	virtual void Render(const RenderParam& param);
	virtual void Update(float dt);
	virtual bool OnClicked(const Vector2& pos);
	virtual bool ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType);
private:
	uint m_unCheckIndex;

};
#endif//__UIRADIOGROUP_H_
