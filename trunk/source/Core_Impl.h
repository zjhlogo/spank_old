/*!
 * \file Core_Impl.h
 * \date 7-25-2011 10:11:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __CORE_IMPL_H__
#define __CORE_IMPL_H__

#include <ICore.h>

class Core_Impl : public ICore
{
public:
	Core_Impl();
	virtual ~Core_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual INode* GetRootNode();

	virtual void Update(float dt);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

private:
	bool Init();
	void Term();

private:
	INode* m_pRootNode;

};
#endif // __CORE_IMPL_H__
