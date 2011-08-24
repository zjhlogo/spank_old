/*!
 * \file Core_Impl.cpp
 * \date 7-25-2011 10:13:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Core_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>
#include <util/IFileUtil.h>
#include <msg/MsgMgr.h>
#include <util/ScreenUtil.h>
#include <InputMgr.h>
#include <IRenderDevice.h>
#include <ITextureMgr.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>
#include <ui/IRendererUI.h>
#include <ui/IFontMgr.h>
#include <ui/IUISystem.h>
#include <IGameApp.h>
#include "Node_Impl.h"

ICore& ICore::GetInstance()
{
	static Core_Impl s_Core_Impl;
	return s_Core_Impl;
}

Core_Impl::Core_Impl()
{
	m_pRootNode = NULL;
}

Core_Impl::~Core_Impl()
{
	// TODO: 
}

bool Core_Impl::PreInitialize()
{
	m_pRootNode = new Node_Impl();
	return true;
}

bool Core_Impl::Initialize()
{
	if (!ConfigUtil::GetInstance().Initialize()) return false;
	if (!IDebugUtil::GetInstance().Initialize()) return false;
	if (!IFileUtil::GetInstance().Initialize()) return false;
	if (!MsgMgr::GetInstance().Initialize()) return false;
	if (!ScreenUtil::GetInstance().Initialize()) return false;
	if (!InputMgr::GetInstance().Initialize()) return false;
	if (!IRenderDevice::GetInstance().Initialize()) return false;
	if (!ITextureMgr::GetInstance().Initialize()) return false;
	if (!IShaderMgr::GetInstance().Initialize()) return false;
	if (!IRenderer2D::GetInstance().Initialize()) return false;
	if (!IRendererUI::GetInstance().Initialize()) return false;
	if (!IFontMgr::GetInstance().Initialize()) return false;
	if (!IUISystem::GetInstance().Initialize()) return false;
	if (!PreInitialize()) return false;
	if (!IGameApp::GetInstance().Initialize()) return false;

	if (!PostInitialize()) return false;
	return true;
}

bool Core_Impl::PostInitialize()
{
	m_pRootNode->UpdateMatrix(0.0f);
	return true;
}

void Core_Impl::PreTerminate()
{
	SAFE_DELETE(m_pRootNode);
}

void Core_Impl::Terminate()
{
	IGameApp::GetInstance().Terminate();
	PreTerminate();
	IUISystem::GetInstance().Terminate();
	IFontMgr::GetInstance().Terminate();
	IRendererUI::GetInstance().Terminate();
	IRenderer2D::GetInstance().Terminate();
	IShaderMgr::GetInstance().Terminate();
	ITextureMgr::GetInstance().Terminate();
	IRenderDevice::GetInstance().Terminate();
	InputMgr::GetInstance().Terminate();
	ScreenUtil::GetInstance().Terminate();
	MsgMgr::GetInstance().Terminate();
	IFileUtil::GetInstance().Terminate();
	IDebugUtil::GetInstance().Terminate();
	ConfigUtil::GetInstance().Terminate();

	PostTerminate();
}

void Core_Impl::PostTerminate()
{
	// nothing to do
}

INode* Core_Impl::GetRootNode()
{
	return 	m_pRootNode;
}

void Core_Impl::PreUpdate(float dt)
{
	MsgMgr::GetInstance().DispatchMessage();
}

void Core_Impl::Update(float dt)
{
	PreUpdate(dt);

	IGameApp::GetInstance().Update(dt);
	IUISystem::GetInstance().Update(dt);

	PostUpdate(dt);
}

void Core_Impl::PostUpdate(float dt)
{
	// update actions
	m_pRootNode->UpdateAction(dt);

	// update objects
	m_pRootNode->UpdateObjects(dt);

	// update matrix
	m_pRootNode->UpdateMatrix(dt);
}

void Core_Impl::PreRender()
{
	// render system objects
	m_pRootNode->RenderObjects();
}

void Core_Impl::Render()
{
	IRenderDevice::GetInstance().BeginRender();
	PreRender();

	IRenderer2D::GetInstance().BeginRender();
	IGameApp::GetInstance().Render();
	IRenderer2D::GetInstance().EndRender();

	IUISystem::GetInstance().Render();

	PostRender();
	IRenderDevice::GetInstance().EndRender();
}

void Core_Impl::PostRender()
{
	// TODO: 
}
