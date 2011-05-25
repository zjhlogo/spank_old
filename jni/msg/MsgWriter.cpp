/*!
 * \file MsgWriter.cpp
 * \date 20-05-2011 00:01:35
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "MsgWriter.h"
#include "MsgID.h"

MsgWriter::MsgWriter(int nMsgID)
:MsgBase(nMsgID)
{
	m_pWriter = new StreamWriter();
}

MsgWriter::~MsgWriter()
{
	if (m_pWriter)
	{
		delete m_pWriter;
		m_pWriter = NULL;
	}
}

bool MsgWriter::Pack(StreamWriter* pWriter)
{
	pWriter->Write(m_pWriter->GetBuffer(), m_pWriter->GetBufferSize());
	return true;
}

bool MsgWriter::Unpack(StreamReader* pReader)
{
	return false;
}

bool MsgWriter::FromBuffer(StreamReader* pReader)
{
	return false;
}
