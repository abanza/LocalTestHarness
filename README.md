# Local Test Harness

Developing software application consist of several packages or library modules that require frequent testing. If the application is complex, we might want to build it step-by-step. First, we design and implement a basic feature with a few modules, then add features incrementally to an existing module library. Each time we add feature, we build and test. That way, if something breaks, we know where to look, for example, in the newly added feature. A test harness allows us to use that step-by-step approach efficiently. 

A test harness allows us to define and aggregate several minor tests, each of which can run with exception handling and results logging. The goal is to accomplish that without cluttering the program with many try-catch blocks and several logging. We can define in the test harness program, an execution method that takes a callable test object, a function pointer, a functor or lambda, and invokes the object in the scope of the try block. 

We can also have, a catch clause that shows exceptions and returns false to indicate test failure. Or else the executor returns the test predicate returned by the test object, for example, a true or false for pass or fail. The executor can also offer results logging with predefined messages. 

In addition, the test harness defines several levels of loggin, for example, pass or fail, or more detailed, test-specific messages, or very detailed debugging messages, which display a time-data stamp and the values of key test-defined variables. 

The test harness program provides a mechanism to link any number of tests into a test sequence. Naturally, during development, we keep adding tests for each new feature, and can rebuild tests specifically for that feature, or all the tests of all the features, to ensure that the new feature didn’t break existing features. 

The test harness program uses Visual Studio Windows edition, and it’s written in the standard C++ programming language, using the standard C++ libraries.

### The TestHarness program has the following:

1.	The program provides packages for an Executive, TestHarness, Logger, and FileManager.

2.	Accept a TestRequest XML string defining one or more test elements, aming dynamic link libraries. 

3.	Each test element contains a testDriver element and one or more testedCode elements, naming dynamic link libraries. 

4.	testDrivers implement an ITest interface that declares a test method taking no arguments and returning a Boolean value indicating test pass or failure.

5.	The TestDriver library also define a factory method of creating instances of the test driver. 

6.	On receiving a TestRequest, the TestHarness parse the request, load the corresponding libraries, sequentially create instances of each TestDriver using its factory method, and log pass-fail status of each test, along with a time-date stamp.

7.	The program provides one or more TestRequests that conduct testing of at least three of the packages.

8.	The Executive package provide processing to demonstrate that these requirements are met, by using facilities of the TestHarness program. 

