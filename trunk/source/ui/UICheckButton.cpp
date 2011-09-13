/*!
 * \file UICheckButton.cpp
 * \date 2011/09/09 11:23
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UICheckButton.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <msg/MsgClick.h>

UICheckButton::UICheckButton(UIWindow* pParent)
:UIWindow(pParent)
{
	m_pString = new UIString(NULL);
	m_bCheck = false;
	// load default state styles
	IUIResMgr::GetInstance().SetupDefaultCheckButtonTextures(m_pStyle);
}

UICheckButton::~UICheckButton()
{
	SAFE_DELETE(m_pString);
}

void UICheckButton::Update(float dt)
{
	// TODO: 
}

void UICheckButton::Render(const RenderParam& param)
{
	Vector2 posAbs = param.m_vBasePos + GetPosition();

	if (IsChecked())
	{
		if (!IsEnable() || !param.IsEnable())
		{
			// render disabled state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_CHECK_DISABLED]);
			// TODO: render string disabled state
			m_pString->Render(posAbs);
		}
		else if (IsPressed())
		{
			// render pressed state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_CHECK_PRESSED]);
			// TODO: render string pressed state
			m_pString->Render(posAbs);
		}
		else
		{
			// render default state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_CHECK]);
			// TODO: render string pressed state
			m_pString->Render(posAbs);
		}
	}
	else
	{
		if (!IsEnable() || !param.IsEnable())
		{
			// render disabled state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_UNCHECK_DISABLED]);
			// TODO: render string disabled state
			m_pString->Render(posAbs);
		}
		else if (IsPressed())
		{
			// render pressed state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_UNCHECK_PRESSED]);
			// TODO: render string pressed state
			m_pString->Render(posAbs);
		}
		else
		{
			// render default state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_UNCHECK]);
			// TODO: render string pressed state
			m_pString->Render(posAbs);
		}
	}
}

Vector2 UICheckButton::GetBestSize()
{
	Vector2 sizeImage(m_pStyle[DUS_CHECKBUTTON_CHECK]->width, m_pStyle[DUS_CHECKBUTTON_CHECK]->height);
	const Vector2& sizeString = m_pString->GetSize();
	float width = sizeImage.x+sizeString.x;
	float height = sizeImage.y > sizeString.y ? sizeImage.y : sizeString.y;
	return Vector2(width, height);
}

void UICheckButton::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
	AdjustSize();
}

void UICheckButton::SetCheck(bool bCheck)
{
	m_bCheck = bCheck;
}

bool UICheckButton::IsChecked() const
{
	return m_bCheck;
}

bool UICheckButton::SetCheckButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex)
{
	if (nIndex < 0 || nIndex >= DUS_CHECKBUTTON_NUM) return false;
	m_pStyle[nIndex] = pImagePiece;
	AdjustSize();

	return true;
}

bool UICheckButton::OnClicked(const Vector2& pos)
{
	m_bCheck = !m_bCheck;
	// TODO: notify msg event
	return true;
}
