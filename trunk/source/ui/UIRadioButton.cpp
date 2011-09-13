/*!
 * \file UIRadioButton.cpp
 * \date 2011/09/08 10:17
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIRadioButton.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>

UIRadioButton::UIRadioButton(UIWindow* pParent)
:UIWindow(pParent)
{
	m_nGroupID = 1;
	m_pString = new UIString(NULL);
	m_bCheck = false;

	IUIResMgr::GetInstance().SetupDefaultRadioButtonTextures(m_pStyle, DUS_RADIOBUTTON_NUM);
}

UIRadioButton::~UIRadioButton()
{
	SAFE_DELETE(m_pString);
}

void UIRadioButton::Update(float dt)
{
	// TODO: 
}

void UIRadioButton::Render(const RenderParam& param)
{
	Vector2 posAbs = param.m_vBasePos + GetPosition();

	if (IsChecked())
	{
		if (!IsEnable() || !param.IsEnable())
		{
			// render disabled state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_RADIOBUTTON_CHECK_DISABLED]);
			// TODO: render string disabled state
			m_pString->Render(posAbs);
		}
		else if (IsPressed())
		{
			// render pressed state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_RADIOBUTTON_CHECK_PRESSED]);
			// TODO: render string pressed state
			m_pString->Render(posAbs);
		}
		else
		{
			// render default state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_RADIOBUTTON_CHECK]);
			// TODO: render string pressed state
			m_pString->Render(posAbs);
		}
	}
	else
	{
		if (!IsEnable() || !param.IsEnable())
		{
			// render disabled state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_RADIOBUTTON_UNCHECK_DISABLED]);
			// TODO: render string disabled state
			m_pString->Render(posAbs);
		}
		else if (IsPressed())
		{
			// render pressed state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_RADIOBUTTON_UNCHECK_PRESSED]);
			// TODO: render string pressed state
			m_pString->Render(posAbs);
		}
		else
		{
			// render default state
			IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_RADIOBUTTON_UNCHECK]);
			// TODO: render string pressed state
			m_pString->Render(posAbs);
		}
	}
}

Vector2 UIRadioButton::GetBestSize()
{
	Vector2 sizeImage(m_pStyle[DUS_RADIOBUTTON_CHECK]->width, m_pStyle[DUS_RADIOBUTTON_CHECK]->height);
	const Vector2& sizeString = m_pString->GetSize();
	float width = sizeImage.x+sizeString.x;
	float height = sizeImage.y > sizeString.y ? sizeImage.y : sizeString.y;
	return Vector2(width, height);
}

void UIRadioButton::SetGroupID(int nGroup)
{
	m_nGroupID = nGroup;
	// TODO: join to a new group
}

int UIRadioButton::GetGroupID() const
{
	return m_nGroupID;
}

void UIRadioButton::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
	AdjustSize();
}

void UIRadioButton::SetCheck(bool bCheck)
{
	m_bCheck = bCheck;
	// TODO: remove the old check one
}

bool UIRadioButton::IsChecked() const
{
	return m_bCheck;
}

bool UIRadioButton::SetRadioButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex)
{
	if (nIndex < 0 || nIndex >= DUS_RADIOBUTTON_NUM) return false;
	m_pStyle[nIndex] = pImagePiece;
	AdjustSize();

	return true;
}

bool UIRadioButton::OnClicked(const Vector2& pos)
{
	// TODO: change status and send message
	return true;
}
