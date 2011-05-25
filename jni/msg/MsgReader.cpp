/*!
 * \file MsgReader.cpp
 * \date 20-05-2011 20:45:24
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "MsgReader.h"
#include "MsgWriter.h"
#include "MsgID.h"
#include <cstddef>

MsgReader::MsgReader(StreamReader* pReader)
:MsgBase(MI_UNKNOWN)
{
	m_pReader = NULL;
	FromBuffer(pReader);
}

MsgReader::~MsgReader()
{
	if (m_pReader)
	{
		delete m_pReader;
		m_pReader = NULL;
	}
}

bool MsgReader::Pack(StreamWriter* pWriter)
{
	return false;
}

bool MsgReader::Unpack(StreamReader* pReader)
{
	m_pReader = new StreamReader(pReader->GetBuffer(), pReader->GetSize());
	return true;
}

bool MsgReader::ToBuffer(StreamWriter* pWriter)
{
	return false;
}
