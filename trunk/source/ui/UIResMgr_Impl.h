/*!
 * \file UIResMgr_Impl.h
 * \date 8-22-2011 15:33:13
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIRESMGR_IMPL_H__
#define __UIRESMGR_IMPL_H__

#include <ui/IUIResMgr.h>
#include <msg/IMsgBase.h>
#include <map>
#include <string>

class UIResMgr_Impl : public IUIResMgr
{
public:
	typedef std::map<std::string, IFont*> TM_FONT;

public:
	UIResMgr_Impl();
	virtual ~UIResMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual IFont* CreateFont(const char* pszFontFile);
	virtual IFont* GetDefaultFont();

	virtual bool SetupDefaultButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_BUTTON_NUM) const;
	virtual bool SetupDefaultCheckButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_CHECKBUTTON_NUM) const;
	virtual bool SetupDefaultRadioButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_RADIOBUTTON_NUM) const;

private:
	IFont* FindFont(const char* pszFontFile);
	bool OnFontDestroied(IMsgBase* pMsg);

	bool InitDefaultButtonStyle();
	bool InitDefaultCheckButtonStyle();
	bool InitDefaultRadioButtonStyle();

private:
	TM_FONT m_mapFont;
	IFont* m_pDefaultFont;

	const IMAGE_PIECE* m_pButtonStyle[DUS_BUTTON_NUM];
	const IMAGE_PIECE* m_pCheckButtonStyle[DUS_CHECKBUTTON_NUM];
	const IMAGE_PIECE* m_pRadioButtonStyle[DUS_RADIOBUTTON_NUM];

};
#endif // __UIRESMGR_IMPL_H__
