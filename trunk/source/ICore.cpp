/*!
 * \file ICore.cpp
 * \date 23-07-2011 11:17:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ICore.h>
#include <IConfig.h>
#include <IDebugUtil.h>
#include <IFileMgr.h>
#include <IRenderDevice.h>
#include <ITextureMgr.h>
#include <IGameMain.h>

ICore& ICore::GetInstance()
{
	static ICore s_ICore;
	return s_ICore;
}

bool ICore::Initialize()
{
	if (!IConfig::GetInstance().Initialize()) return false;
	if (!IDebugUtil::GetInstance().Initialize()) return false;
	if (!IFileMgr::GetInstance().Initialize()) return false;
	if (!IRenderDevice::GetInstance().Initialize()) return false;
	if (!ITextureMgr::GetInstance().Initialize()) return false;
	if (!IGameMain::GetInstance().Initialize()) return false;
	return true;
}

void ICore::Terminate()
{
	IGameMain::GetInstance().Terminate();
	ITextureMgr::GetInstance().Terminate();
	IRenderDevice::GetInstance().Terminate();
	IFileMgr::GetInstance().Terminate();
	IDebugUtil::GetInstance().Terminate();
	IConfig::GetInstance().Terminate();
}

void ICore::Update(float dt)
{
	IGameMain::GetInstance().Update(dt);
}

void ICore::PreRender()
{
	IRenderDevice::GetInstance().BeginRender();
}

void ICore::Render()
{
	IGameMain::GetInstance().Render();
}

void ICore::PostRender()
{
	IRenderDevice::GetInstance().EndRender();
}
