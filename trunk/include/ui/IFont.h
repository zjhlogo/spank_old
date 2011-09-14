/*!
 * \file IFont.h
 * \date 8-22-2011 14:20:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IFONT_H__
#define __IFONT_H__

#include "../IObject.h"
#include "BaseTypeUI.h"

class IFont : public IObject
{
public:
	DECLARE_RTTI(IFont, IObject);

	virtual float GetLineHeight() const = 0;
	virtual const CHAR_INFO* GetCharInfo(int nID) const = 0;
	virtual float GetKerning(int nFirstID, int nSecondID) const = 0;

protected:
	IFont() {};
	virtual ~IFont() {};

};

#endif // __IFONT_H__
