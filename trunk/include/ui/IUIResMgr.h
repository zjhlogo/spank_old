/*!
 * \file IUIResMgr.h
 * \date 8-22-2011 15:31:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IUIRESMGR_H__
#define __IUIRESMGR_H__

#include "BaseTypeUI.h"
#include "IFont.h"
#include "../IMgr.h"

class IUIResMgr : public IMgr
{
public:
	DECLARE_RTTI(IUIResMgr, IMgr);

	static IUIResMgr& GetInstance();

	virtual IFont* CreateFont(const char* pszFontFile) = 0;
	virtual IFont* GetDefaultFont() = 0;

	virtual bool SetupDefaultButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_BUTTON_NUM) const = 0;
	virtual bool SetupDefaultCheckButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_CHECKBUTTON_NUM) const = 0;
	virtual bool SetupDefaultRadioButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_RADIOBUTTON_NUM) const = 0;

};
#endif // __IUIRESMGR_H__
