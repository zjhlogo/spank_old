/*!
 * \file IMgr.h
 * \date 23-07-2011 08:19:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMGR_H__
#define __IMGR_H__

class IMgr
{
public:
	virtual bool Initialize() = 0;
	virtual void Terminate() = 0;

};
#endif // __IMGR_H__
