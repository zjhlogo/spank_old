/*!
 * \file UIDesignerApp.h
 * \date 8-31-2011 13:05:16
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIDESIGNERAPP_H__
#define __UIDESIGNERAPP_H__

#include <wx/app.h>
#include <wx/image.h>

class UIDesignerApp : public wxApp
{
public:
	UIDesignerApp();
	virtual ~UIDesignerApp();

	virtual bool OnInit();

};

#endif // __UIDESIGNERAPP_H__
