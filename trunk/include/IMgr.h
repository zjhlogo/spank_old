/*!
 * \file IMgr.h
 * \date 23-07-2011 08:19:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMGR_H__
#define __IMGR_H__

#include "msg/IMsgHandler.h"

/*! \brief base class of all management classes
 *
 * all managerment classes should inheritance from IMgr to initialize itself by
 * override the pure virtual function Initialize(), and terminate the classse
 * by override the pure virtual function Terminate().
 */
class IMgr : public IMsgHandler
{
public:
	DECLARE_RTTI(IMgr, IMsgHandler);

	/*!
	 * \brief initialize the instance
	 *
	 * initialize all data (ex. memory allocate, ...) inside the function
	 * \return if initialize success return true, otherwise return false
	 */
	virtual bool Initialize() = 0;
	
	/*!
	 * \brief terminate the instance
	 *
	 * release all data (ex. memory release, ...) inside the function
	 */
	virtual void Terminate() = 0;

};
#endif // __IMGR_H__
