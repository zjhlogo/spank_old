/*!
 * \file MsgCommon.h
 * \date 8-16-2011 13:59:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGCOMMON_H__
#define __MSGCOMMON_H__

#include "IMsgBase.h"
#include "../IObject.h"

class MsgCommon : public IMsgBase
{
public:
	DECLARE_RTTI(MsgCommon, IMsgBase);

	MsgCommon(uint nMsgID);
	virtual ~MsgCommon();

	uint GetData() const;
	void SetData(uint nData);

	void* GetDataPtr() const;
	void SetDataPtr(void* pData);

	IObject* GetObject() const;
	void SetObject(IObject* pObject);

private:
	uint m_nData;
	void* m_pData;
	IObject* m_pObject;

};
#endif // __MSGCOMMON_H__
