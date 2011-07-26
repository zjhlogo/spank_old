/*!
 * \file WinMain.cpp
 * \date 7-21-2011 11:55:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "WinMain.h"
#include <windows.h>
#include <IConfig.h>
#include <ICore.h>

void EnterMessageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	bool run = true;
	while (run)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			if(msg.message == WM_QUIT)
			{
				run = false;
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ICore::GetInstance().Update(0.0f);

		ICore::GetInstance().PreRender();
		ICore::GetInstance().Render();
		ICore::GetInstance().PostRender();
	}
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	IConfig::GetInstance().AddString("WINDOW_CLASS", "SPANK");
	IConfig::GetInstance().AddString("WINDOW_TITLE", "spank");
	IConfig::GetInstance().AddString("RESOURCE_DIR", ".\\data\\");
	IConfig::GetInstance().AddInt("WINDOW_WIDTH", WindowConfig::WINDOW_WIDTH);
	IConfig::GetInstance().AddInt("WINDOW_HEIGHT", WindowConfig::WINDOW_HEIGHT);

	if (ICore::GetInstance().Initialize())
	{
		EnterMessageLoop();
		ICore::GetInstance().Terminate();
	}

	return 0;
}
