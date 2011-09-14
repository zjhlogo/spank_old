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
#include "../ISingleton.h"

class IUIResMgr : public ISingleton
{
public:
	DECLARE_RTTI(IUIResMgr, ISingleton);

	static IUIResMgr& GetInstance();

	virtual IFont* CreateFont(const char* pszFontFile) = 0;
	virtual IFont* GetDefaultFont() = 0;

	virtual bool AddImageFrame(const char* pszFrameFile) = 0;
	virtual const IMAGE_FRAME* FindImageFrame(const char* pszFrameName) const = 0;

	virtual const IMAGE_FRAME* GetDefaultImageFrame() const = 0;
	virtual const IMAGE_FRAME* GetPressedImageFrame() const = 0;
	virtual const IMAGE_FRAME* GetDisabledImageFrame() const = 0;

	virtual bool SetupDefaultButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_BUTTON_NUM) const = 0;
	virtual bool SetupDefaultCheckButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_CHECKBUTTON_NUM) const = 0;
	virtual bool SetupDefaultRadioButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_RADIOBUTTON_NUM) const = 0;

};
#endif // __IUIRESMGR_H__
