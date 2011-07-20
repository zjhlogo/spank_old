/*!
 * \file StreamWriter.h
 * \date 18-05-2011 22:55:52
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __STREAMWRITER_H__
#define __STREAMWRITER_H__

#include <cstddef>

class StreamWriter
{
public:
	enum CONST_DEFINE
	{
		BLOCK_ALIGN = 128,
	};

public:
	StreamWriter();
	~StreamWriter();

	bool Write(const void* pData, int nSize);

	const void* GetBuffer();
	int GetBufferSize();

private:
	bool Expend(int nRequireSize);

private:
	char* m_pBuffer;
	int m_nSize;
	int m_nPos;

};
#endif // __STREAMWRITER_H__
