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
#include <msg/MsgButtonSelect.h>
UICheckButton::UICheckButton(UIWindow* pParent)
:UIWindow(pParent)
{
	m_pString = new UIString(NULL);
	m_bCheck = false;
	// load default state styles
	IUIResMgr::GetInstance().SetupDefaultCheckButtonTextures(m_pStyle);
	AdjustSize();
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
	RenderBorder(param);

	Vector2 posAbs = param.m_vBasePos + GetPosition();
	
	//calculate the off size of string in the right;
	Vector2 posStroff = (GetSize() - m_pString->GetSize());
	if (IsChecked())
	{
		if (!IsEnable() || !param.IsEnable())
		{
			// render disabled state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_CHECK_DISABLED]);
			// TODO: render string disabled state
			m_pString->Render(posAbs + posStroff);
		}
		else if (IsPressed())
		{
			// render pressed state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_CHECK_PRESSED]);
			// TODO: render string pressed state
			m_pString->Render(posAbs + posStroff);
		}
		else
		{
			// render default state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_CHECK]);
			// TODO: render string pressed state
			m_pString->Render(posAbs + posStroff);
		}
	}
	else
	{
		if (!IsEnable() || !param.IsEnable())
		{
			// render disabled state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_UNCHECK_DISABLED]);
			// TODO: render string disabled state
			m_pString->Render(posAbs + posStroff);
		}
		else if (IsPressed())
		{
			// render pressed state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_UNCHECK_PRESSED]);
			// TODO: render string pressed state
			m_pString->Render(posAbs + posStroff);
		}
		else
		{
			// render default state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_CHECKBUTTON_UNCHECK]);
			// TODO: render string pressed state
			m_pString->Render(posAbs + posStroff);
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

bool UICheckButton::SetCheck(bool bCheck)
{
	if (m_bCheck == bCheck) return false;
	m_bCheck = bCheck;
	return true;
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
	MsgButtonSelect msgButtonSelect(m_bCheck);
	CallEvent(msgButtonSelect);
	return true;
}
