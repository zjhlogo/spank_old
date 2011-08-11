/*!
 * \file ScreenUtil.h
 * \date 8-11-2011 11:27:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SCREENUTIL_H__
#define __SCREENUTIL_H__

#include "../IMgr.h"
#include "../math/Vector2.h"

class ScreenUtil : public IMgr
{
public:
	enum SCREEN_ROTATION
	{
		SR_NONE = 0,
		SR_P90,
		SR_N90,
		SR_180,
		NUM_SR,
	};

public:
	ScreenUtil();
	virtual ~ScreenUtil();

	static ScreenUtil& GetInstance();

	virtual bool Initialize();
	virtual void Terminate();

	int GetScreenWidth() const;
	int GetScreenHeight() const;

	SCREEN_ROTATION GetScreenRotation() const;
	float GetRotationDegree() const;

	void DevicePointToScreen(Vector2& vPosOut, float x, float y);
	void DevicePointToScreen(Vector2& vPosOut, const Vector2& pos);
	void DevicePointToScreen(Vector2& vPosInOut);

private:
	int m_nScreenWidth;
	int m_nScreenHeight;
	SCREEN_ROTATION m_eScreenRotation;

};
#endif // __SCREENUTIL_H__
