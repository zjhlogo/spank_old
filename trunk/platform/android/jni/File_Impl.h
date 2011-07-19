/*!
 * \file File_Impl.h
 * \date 19-07-2011 22:31:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __FILE_IMPL_H__
#define __FILE_IMPL_H__

#include <IFile.h>

class File_Impl : public IFile
{
public:
	File_Impl();
	virtual ~File_Impl();

	bool OpenFile(const char* pszFileName);

	virtual uint Read(void* pBuffOut, uint nSize);
	virtual uint Write(const void* pBuffIn, uint nSize);
	virtual uint Seek(uint nOffset);
	virtual uint GetSize() const;
	virtual uint Tell() const;

};
#endif // __FILE_IMPL_H__