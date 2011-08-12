/*!
 * \file IObject.h
 * \date 7-25-2011 14:07:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IOBJECT_H__
#define __IOBJECT_H__

#include "msg/IMsgHandler.h"

class IObject : public IMsgHandler
{
public:
	IObject():m_bOK(false), m_nRef(1), m_pParent(NULL) {};
	virtual ~IObject(){};

	bool IsOK() const {return m_bOK;};
	void Release() {if (DecRef() <= 0) delete this;};

	IObject* GetParent() const {return m_pParent;};
	void SetParent(IObject* pParent) {m_pParent = pParent;};

	int IncRef() {return ++m_nRef;};
	int DecRef() {return --m_nRef;};
	int GetRef() const {return m_nRef;};

protected:
	bool m_bOK;

private:
	int m_nRef;
	IObject* m_pParent;

};
#endif // __IOBJECT_H__
