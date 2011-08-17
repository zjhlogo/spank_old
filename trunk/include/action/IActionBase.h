/*!
 * \file IActionBase.h
 * \date 8-16-2011 10:38:20
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IACTIONBASE_H__
#define __IACTIONBASE_H__

#include "../IObject.h"
#include "../math/IMath.h"
#include "../BaseTypeEx.h"

class IActionBase : public IObject
{
public:
	IActionBase(int nID = 0);
	virtual ~IActionBase();

	int GetID() const;

	const Vector3& GetScale() const;
	void SetScale(const Vector3& scale);
	void SetScale(float x, float y, float z);

	const Vector3& GetPosition() const;
	void SetPosition(const Vector3& pos);
	void SetPosition(float x, float y, float z);

	const Quaternion& GetRotation() const;
	void SetRotation(const Quaternion& rot);
	void SetRotation(const Vector3& dir, float fRadian);

	bool IsRunning() const;

	void Start();
	void Stop();
	void Pause();
	void Restart();

	virtual void Reset() = 0;
	virtual void Update(float dt) = 0;

	virtual IActionBase* Clone() = 0;
	virtual IActionBase* CloneInverse() = 0;

	virtual float GetTimeLength() const = 0;

private:
	bool SetRunning(bool running);
	void NotifyActionUpdate(ACTION_UPDATE_TYPE eType);

private:
	int m_nID;
	Vector3 m_vScale;
	Vector3 m_vPosition;
	Quaternion m_qRotation;
	bool m_bRunning;

};
#endif // __IACTIONBASE_H__
