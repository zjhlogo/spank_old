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
#include <IRenderDevice.h>
#include <ITextureMgr.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>
#include <InputMgr.h>
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

bool Core_Impl::Initialize()
{
	if (!ConfigUtil::GetInstance().Initialize()) return false;
	if (!IDebugUtil::GetInstance().Initialize()) return false;
	if (!IFileUtil::GetInstance().Initialize()) return false;
	if (!MsgMgr::GetInstance().Initialize()) return false;
	if (!ScreenUtil::GetInstance().Initialize()) return false;
	if (!IRenderDevice::GetInstance().Initialize()) return false;
	if (!ITextureMgr::GetInstance().Initialize()) return false;
	if (!IShaderMgr::GetInstance().Initialize()) return false;
	if (!IRenderer2D::GetInstance().Initialize()) return false;
	if (!InputMgr::GetInstance().Initialize()) return false;
	if (!Init()) return false;
	if (!IGameApp::GetInstance().Initialize()) return false;

	return true;
}

void Core_Impl::Terminate()
{
	IGameApp::GetInstance().Terminate();
	Term();
	InputMgr::GetInstance().Terminate();
	IRenderer2D::GetInstance().Terminate();
	IShaderMgr::GetInstance().Terminate();
	ITextureMgr::GetInstance().Terminate();
	IRenderDevice::GetInstance().Terminate();
	ScreenUtil::GetInstance().Terminate();
	MsgMgr::GetInstance().Terminate();
	IFileUtil::GetInstance().Terminate();
	IDebugUtil::GetInstance().Terminate();
	ConfigUtil::GetInstance().Terminate();
}

INode* Core_Impl::GetRootNode()
{
	return 	m_pRootNode;
}

void Core_Impl::Update(float dt)
{
	MsgMgr::GetInstance().DispatchMessage();
	IGameApp::GetInstance().Update(dt);
}

void Core_Impl::PreRender()
{
	IRenderDevice::GetInstance().BeginRender();
	IRenderer2D::GetInstance().BeginRender2D();
}

void Core_Impl::Render()
{
	IGameApp::GetInstance().Render();
}

void Core_Impl::PostRender()
{
	IRenderer2D::GetInstance().EndRender2D();
	IRenderDevice::GetInstance().EndRender();
}

bool Core_Impl::Init()
{
	m_pRootNode = new Node_Impl();
	return true;
}

void Core_Impl::Term()
{
	SAFE_DELETE(m_pRootNode);
}