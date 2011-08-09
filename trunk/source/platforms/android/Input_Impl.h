/*!
 * \file Input_Impl.h
 * \date 8-09-2011 17:52:16
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __INPUT_IMPL_H__
#define __INPUT_IMPL_H__

#include <IInput.h>

class Input_Impl : public IInput
{
public:
	enum TOUCH_TYPE
	{
		TT_UNKNOWN = 0,
		TT_BEGIN,
		TT_MOVE,
		TT_END,
	};

	typedef struct TOUCH_INFO_tag
	{
		TOUCH_TYPE eType;
		float x, y;
	} TOUCH_INFO;

public:
	Input_Impl();
	virtual ~Input_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void OnTouchStart(int nIndex, float x, float y);
	virtual void OnTouch(int nIndex, float x, float y);
	virtual void OnTouchEnd(int nIndex, float x, float y);

	virtual void DispatchTouchEvents();

};
#endif // __INPUT_IMPL_H__
