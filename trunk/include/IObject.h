/*!
 * \file IObject.h
 * \date 7-25-2011 14:07:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IOBJECT_H__
#define __IOBJECT_H__

#include "BaseType.h"

class IObject
{
public:
	IObject():m_bOK(false), m_nRef(1){};
	virtual ~IObject(){};

	bool IsOK() const {return m_bOK;};
	virtual void Release() {if (DecRef() <= 0) delete this;};

	int IncRef() {return ++m_nRef;};
	int DecRef() {return --m_nRef;};
	int GetRef() const {return m_nRef;};

protected:
	bool m_bOK;

private:
	int m_nRef;

};
#endif // __IOBJECT_H__
