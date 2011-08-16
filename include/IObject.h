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
	IObject();
	virtual ~IObject();

	bool IsOK() const;
	void Release();

	IObject* GetParent() const;
	void SetParent(IObject* pParent);

	int IncRef();
	int DecRef();
	int GetRef() const;

protected:
	bool m_bOK;

private:
	int m_nRef;
	IObject* m_pParent;

};
#endif // __IOBJECT_H__
