/*!
 * \file ICore.h
 * \date 23-07-2011 11:14:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ICORE_H__
#define __ICORE_H__

#include "ISingleton.h"
#include "INode.h"

class ICore : public ISingleton
{
public:
	DECLARE_RTTI(ICore, ISingleton);

	static ICore& GetInstance();

	virtual INode* GetRootNode() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

};
#endif // __ICORE_H__
