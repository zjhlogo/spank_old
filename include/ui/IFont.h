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
#include "../ITexture.h"

class IFont : public IObject
{
public:
	typedef struct CHAR_INFO_tag
	{
		int nID;
		int width, height;
		float u, v, du, dv;
		ITexture* pTexture;
		int offsetx, offsety, advance;
		int nRef;
	} CHAR_INFO;

public:
	virtual int GetLineHeight() const = 0;
	virtual const CHAR_INFO* GetCharInfo(int nID) const = 0;
	virtual int GetKerning(int nFirstID, int nSecondID) const = 0;

protected:
	IFont() {};
	virtual ~IFont() {};

};

#endif // __IFONT_H__
