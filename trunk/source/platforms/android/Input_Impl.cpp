/*!
 * \file Input_Impl.cpp
 * \date 8-09-2011 17:52:21
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Input_Impl.h"

IInput& IInput::GetInstance()
{
	static Input_Impl s_Input_Impl;
	return s_Input_Impl;
}

Input_Impl::Input_Impl()
{
	// TODO: 
}

Input_Impl::~Input_Impl()
{
	// TODO: 
}

bool Input_Impl::Initialize()
{
	// TODO: 
	return true;
}

void Input_Impl::Terminate()
{
	// TODO: 
}

void Input_Impl::OnTouchStart(int nIndex, float x, float y)
{
	// TODO: 
}

void Input_Impl::OnTouch(int nIndex, float x, float y)
{
	// TODO: 
}

void Input_Impl::OnTouchEnd(int nIndex, float x, float y)
{
	// TODO: 
}

void Input_Impl::DispatchTouchEvents()
{
	// TODO: 
}
