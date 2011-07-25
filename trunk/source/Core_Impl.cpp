/*!
 * \file Core_Impl.cpp
 * \date 7-25-2011 10:13:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Core_Impl.h"
#include <IConfig.h>
#include <IDebugUtil.h>
#include <IFileMgr.h>
#include <IRenderDevice.h>
#include <ITextureMgr.h>
#include <IGameApp.h>

ICore& ICore::GetInstance()
{
	static Core_Impl s_Core_Impl;
	return s_Core_Impl;
}

Core_Impl::Core_Impl()
{
	// TODO: 
}

Core_Impl::~Core_Impl()
{
	// TODO: 
}

bool Core_Impl::Initialize()
{
	if (!IConfig::GetInstance().Initialize()) return false;
	if (!IDebugUtil::GetInstance().Initialize()) return false;
	if (!IFileMgr::GetInstance().Initialize()) return false;
	if (!IRenderDevice::GetInstance().Initialize()) return false;
	if (!ITextureMgr::GetInstance().Initialize()) return false;
	if (!IGameApp::GetInstance().Initialize()) return false;
	return true;
}

void Core_Impl::Terminate()
{
	IGameApp::GetInstance().Terminate();
	ITextureMgr::GetInstance().Terminate();
	IRenderDevice::GetInstance().Terminate();
	IFileMgr::GetInstance().Terminate();
	IDebugUtil::GetInstance().Terminate();
	IConfig::GetInstance().Terminate();
}

void Core_Impl::Update(float dt)
{
	IGameApp::GetInstance().Update(dt);
}

void Core_Impl::PreRender()
{
	IRenderDevice::GetInstance().BeginRender();
}

void Core_Impl::Render()
{
	IGameApp::GetInstance().Render();
}

void Core_Impl::PostRender()
{
	IRenderDevice::GetInstance().EndRender();
}
