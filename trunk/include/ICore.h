/*!
 * \file ICore.h
 * \date 23-07-2011 11:14:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ICORE_H__
#define __ICORE_H__

#include "IMgr.h"
#include "INode.h"

class ICore : public IMgr
{
public:
	static ICore& GetInstance();

	virtual INode* GetRootNode() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

};
#endif // __ICORE_H__
