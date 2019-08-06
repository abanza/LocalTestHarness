///////////////////////////////////////////////////////////////////////////////
// TestExecutor.cpp - TestExecutor class definition                          //
// Author:      Adelard Banza,                                               //
///////////////////////////////////////////////////////////////////////////////
#include <Windows.h>

#include "../Includes/FileManager.h"
#include "../Includes/TestDriver.h"
#include "../Includes/TestHarness.h"
#include "../Includes/TestLogger.h"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::logic_error;
using std::string;

ITest* loadTestDriver(const char*, const string);
bool runTestDriver(const TestingContext&, const TestDriver&);

int main()
{
	// loading the xml files

	// parsing the xml files into a collection of test entries each with a test driver and one or more tested code enties

	bool cumulativeTestingResult = true;

	// setup the testing context for controlling the testing output

	// create a logger for logging the testing output
	Logger logger1;
	logger1.attach(&cout);

	// create a testing contex to bundle the testing settings
	TestingContext testingCtx;
	testingCtx.logger = &logger1;
	testingCtx.reportingLevel = TestHarness::SHOW_ALL_MESSAGES;
	testingCtx.severity = LOGGER_INFO;
	testingCtx.showTimestamp = true;

	// tests is the results
	Tests tests = FileManager::readTestFile("testXML.xml");

	//For each test entry in test
	for (Test test : tests)
	{
		// loop over test drivers in each test
		for (TestDriver test_driver : test._testdrivers)
		{
			cumulativeTestingResult |= runTestDriver(testingCtx, test_driver);
		}
	}

	// report the result of the cumulative testing result

}

bool runTestDriver(const TestingContext& testingCtx, const TestDriver& test_driver)
{
	// run the test, first loading any required dll's and then executing the test driver

	// load the test driver
	const char* libName = test_driver._dll_nm.c_str();
	const string factoryName = test_driver._factory_method_nm;
	ITest* itestHandler = loadTestDriver(libName, factoryName);

	if (itestHandler != nullptr)
	{

		// load any required libraries for our test driver

		// run the test
		itestHandler->setup(&testingCtx, test_driver._tested_codes);
		bool result = itestHandler->runTests();
		itestHandler->teardown();

		// garbage collect the test driver
		if (itestHandler != nullptr)
		{
			delete itestHandler;
			itestHandler = nullptr;
		}

		return result;
	}
	else
	{
		cout << "failed to get test driver" << endl;
	}

	return false;
}

/*
*  Loads the Itest using "Run-Time Dynamic Linking," by loading a dll via LoadLibrary and
*    resolving functions using GetProcAddress.
*
*   Note: The Itest instance must be freed using delete.
*/
ITest* loadTestDriver(const char* libraryName, const string factoryFnName)
{

	size_t len = strlen(libraryName) + 1;

	// to call win32 load library need a w_char-string (2-byte wide char)
	LPWSTR libName = new wchar_t[len];

	size_t outLen;

	// std library function to do convertion
	mbstowcs_s(&outLen, libName, len, libraryName, strlen(libraryName) + 1);

	// here we actually load the dll we are interested in
	HINSTANCE hDLL = LoadLibrary(libName);

	// remember to free the dynamic string
	delete libName;

	// see if the libary was loaded
	if (NULL != hDLL)
	{

		// Load the factory method from out library
		TestFactory factory = (TestFactory)GetProcAddress(hDLL, factoryFnName.c_str());

		// see if we successfully loaded our library
		if (factory != nullptr)
		{
			// success print happy message
			cout << "Loaded factory method " << factoryFnName << "() from library: " << libraryName << endl;

			// now get the ITest interface
			ITest* itest = nullptr;

			factory(&itest);

			if (itest != nullptr)
			{
				return itest;
			}
			else
			{
				// fail print unhappy message
				cerr << "factory method " << factoryFnName << "(): did not return an ITest instance from testing library: " << libraryName << endl;
			}
		}
		else
		{
			// fail print unhappy message
			cerr << "could not load factory method " << factoryFnName << "() from library: " << libraryName << endl;
		}

		// unload library
		FreeLibrary(hDLL);
	}
	else
	{
		cerr << "Load library failed for: " << libraryName << endl;
	}

	return 0;
}