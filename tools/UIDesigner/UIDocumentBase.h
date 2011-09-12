/*!
 * \file UIDocumentBase.h
 * \date 11-09-2011 08:17:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIDOCUMENTBASE_H__
#define __UIDOCUMENTBASE_H__
#include <wx/string.h>

class UIDocumentBase
{
public:
	UIDocumentBase();
	virtual ~UIDocumentBase();

	virtual bool OpenFile(const wxString& strFile) = 0;
	virtual bool SaveFile(const wxString& strFile) = 0;
	virtual const wxString& GetFileName() const = 0;

};
#endif // __UIDOCUMENTBASE_H__
