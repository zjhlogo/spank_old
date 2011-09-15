/*!
 * \file UIButton.h
 * \date 2011/09/05 9:31
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#ifndef __ClipTets_H_
#define __ClipTets_H_

#include <ui/UIWindow.h>
#include <ui/UIString.h>

#include <ITexture.h>

class ClipTest : public UIWindow
{
public:
	DECLARE_RTTI(ClipTest, UIWindow);

	ClipTest(UIWindow* pParent);
	virtual ~ClipTest();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);
	virtual Vector2 GetBestSize();

	virtual bool OnClicked(const Vector2& pos);
	virtual void SetClip(float x, float y, float width, float height);
private:
	const IMAGE_PIECE* m_pStyle[DUS_BUTTON_NUM];
	float m_fx, m_fy, m_fwidth, m_fheight;
};
#endif//__ClipTets_H_
