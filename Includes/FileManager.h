///////////////////////////////////////////////////////////////////////////////
// FileManager.h - FileManager class definition                              //
// Author:      Adelard Banza,                                               //
///////////////////////////////////////////////////////////////////////////////
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../Includes/TestDriver.h"
#include <string>

#ifdef TESTINGHARNESS_EXPORTS // inside the dll
#define TESTING_HARNESS_API    __declspec(dllexport)
#else // outside dll
#define TESTING_HARNESS_API    __declspec(dllimport)
#endif

class TESTING_HARNESS_API FileManager
{
public:
	static Tests readTestFile(const std::string& filename);
};

#endif // !FILE_MANAGER_H
