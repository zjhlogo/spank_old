/*!
 * \file ISingleton.h
 * \date 23-07-2011 08:19:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ISINGLETON_H__
#define __ISINGLETON_H__

#include "msg/IMsgHandler.h"

/*! \brief base class of all singleton classes
 *
 * all managerment classes should inheritance from ISingleton to initialize itself by
 * override the pure virtual function Initialize(), and terminate the classse
 * by override the pure virtual function Terminate().
 */
class ISingleton : public IMsgHandler
{
public:
	DECLARE_RTTI(ISingleton, IMsgHandler);

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
#endif // __ISINGLETON_H__
