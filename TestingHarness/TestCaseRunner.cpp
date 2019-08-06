///////////////////////////////////////////////////////////////////////////////
// TestCaseRunner.cpp - TestCaseRunner class definition                      //
// ver 1.0                                                                   //
// Language:    C++, Visual Studio 2017                                      //
// Platform:    HP G1 800, Windows 10                                        //
// Application: Local Test Harness Project2, CSE687 - Object Oriented Design //
// Author:      Adelard Banza,                                               //
//              abanza@syr.edu                                               //
///////////////////////////////////////////////////////////////////////////////
#include "../Includes/TestHarness.h"

#include <exception>
#include <stdexcept>

using std::exception;
using std::string;

bool TestCaseRunner::run(const std::string& contextStr, TestLogger& testLogger) const
{
	// log the begining of the test case
	testLogger.logTestCaseBegin(contextStr);
	AssertionManager::getInstance().pushCntx(contextStr, &testLogger);

	// a variable to hold the test result
	bool testResult = true;

	// a variable to hold the test message
	string msg;

	try
	{
		// run the test executor function
		testResult = this->testExecutor();

		bool assertResults = AssertionManager::getInstance().popCntx();

		testResult &= assertResults;

		// deal with no excption case
		if (testResult)
		{
			testLogger.logTestCaseSuccess(contextStr);
		}
		else
		{
			testLogger.logTestCaseFail(contextStr);
		}
	}
	catch (std::logic_error e)
	{
		// deal with a standard library exception
		testResult = false;
		testLogger.logTestCaseFailWithSpecificException(contextStr, "logic_error", e);
	}
	catch (exception e)
	{
		// deal with a standard library exception
		testResult = false;
		testLogger.logTestCaseFailWithException(contextStr, e);
	}
	catch (...)
	{
		// deal with an unknown exception type
		testResult = false;
		testLogger.logTestCaseFailWithUnknownException(contextStr);
	}

	return testResult;
}