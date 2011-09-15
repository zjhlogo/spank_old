/*!
 * \file MsgButtonClick.cpp
 * \date 2011/09/14 17:16
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <msg/MsgButtonSelect.h>
#include <msg/MsgID.h>

MsgButtonSelect::MsgButtonSelect( bool bSelect )
:IMsgBase(MI_UI_BUTTON_SELECT)
{
	m_bSelect = bSelect;
}

MsgButtonSelect::~MsgButtonSelect()
{
	//TODO:
}

bool MsgButtonSelect::IsSelect() const
{
	return m_bSelect;
}
