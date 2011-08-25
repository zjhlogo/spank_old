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
#include "../math/IMath.h"

/*! \brief screen coordinate system utility class
 *
 * it is a utility class to manage the screen coordinate system. use this class
 * to convert device coordinate to screen coordinate.
 */
class ScreenUtil : public IMgr
{
public:
	/*! screen rotation enumlate */
	enum SCREEN_ROTATION
	{
		SR_NONE = 0,		/*!< un-rotated, default portrait mode */
		SR_P90,				/*!< rotate screen +90 degree */
		SR_N90,				/*!< rotate screen -90 degree */
		SR_180,				/*!< rotate screen +180 degree */
		NUM_SR,				/*!< numbers of screen rotation enumlation */
	};

public:
	
	/*!
	 * \brief default constructure
	 */
	ScreenUtil();
	
	/*!
	 * \brief default destructure
	 */
	virtual ~ScreenUtil();

	
	/*!
	 * \brief get the instance of ScreenUtil
	 * \return the instance of ScreenUtil
	 */
	static ScreenUtil& GetInstance();

	virtual bool Initialize();
	virtual void Terminate();

	
	/*!
	 * \brief get the screen width (after rotation)
	 * \return the screen width
	 */
	int GetScreenWidth() const;
	
	/*!
	 * \brief get the screen height (after rotation)
	 * \return the screen height
	 */
	int GetScreenHeight() const;

	/*!
	 * \brief get the screen size (after rotation)
	 * \return the screen size, x = width, y = height
	 */
	const Vector2& GetScreenSize() const;
	const Vector2& GetHalfScreenSize() const;

	/*!
	 * \brief get the screen rotation
	 * \return the screen rotation \see SCREEN_ROTATION
	 */
	SCREEN_ROTATION GetScreenRotation() const;
	
	/*!
	 * \brief get the screen rotation degree
	 *
	 * for example if screen rotate by SR_P90 the return value will be -90.0f, 
	 * because the screen rotate by +90.0f, coordinate y will point to left
	 * for keeping the coordinate y up, rotate it back -90.0f degreed. so it 
	 * return the invert of the rotation.
	 * \return the screen rotation degree
	 */
	float GetRotationDegree() const;

	
	/*!
	 * \brief convert device position to screen position
	 * \param vPosOut output vector
	 * \param x device position x
	 * \param y device position y
	 */
	void DevicePointToScreen(Vector2& vPosOut, float x, float y);
	
	/*!
	 * \brief convert device position to screen position
	 * \param vPosOut output vector
	 * \param pos device position
	 */
	void DevicePointToScreen(Vector2& vPosOut, const Vector2& pos);
	
	/*!
	 * \brief convert device position to screen position
	 * \param vPosInOut device position for input and output the screen position
	 */
	void DevicePointToScreen(Vector2& vPosInOut);

private:
	int m_nScreenWidth;						/*!< screen width */
	int m_nScreenHeight;					/*!< screen height */
	Vector2 m_vScreenSize;					/*!< screen size in vector version */
	Vector2 m_vHalfScreenSize;				/*!< half screen size in vector version */
	SCREEN_ROTATION m_eScreenRotation;		/*!< screen rotation */

};
#endif // __SCREENUTIL_H__
