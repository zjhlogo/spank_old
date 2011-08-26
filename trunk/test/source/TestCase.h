/*!
 * \file TestCase.h
 * \date 8-25-2011 9:29:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __TESTCASE_H__
#define __TESTCASE_H__

#include <IObject.h>
#include <ui/UIScreen.h>
#include <msg/IMsgBase.h>
#include <string>

class TestCase : public IObject
{
public:
	TestCase(const char* pszTestName);
	virtual ~TestCase();

	bool InternalInitialize();
	void InternalTerminate();

	virtual bool Initialize(UIScreen* pUIScreen) = 0;
	virtual void Terminate() = 0;

	virtual void Update(float dt);
	virtual void Render();

private:
	void AddReturnButton(UIScreen* pUIScreen);

private:
	std::string m_strTestName;
	UIScreen* m_pUIScreen;

};
#endif // __TESTCASE_H__
