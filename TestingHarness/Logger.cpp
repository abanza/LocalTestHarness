///////////////////////////////////////////////////////////////////////////////
// Logger.cpp - Logger class definition                                      //
// ver 1.0                                                                   //
// Language:    C++, Visual Studio 2017                                      //
// Platform:    HP G1 800, Windows 10                                        //
// Application: Local Test Harness Project2, CSE687 - Object Oriented Design //
// Author:      Adelard Banza,                                               //
//              abanza@syr.edu                                               //
///////////////////////////////////////////////////////////////////////////////
#include "../Includes/TestLogger.h"

#include <iostream>
#include <string>

using std::endl;
/*
* simple no arg contructor creates a Logger with no attached ostreams,
*   and a default severity of INFO
*/
Logger::Logger(void) 
	: log_streams(), severity(LOGGER_INFO) {}

/*
* creates a Logger with a single given attached ostream to output to,
*   and a default severity of INFO
*/
Logger::Logger(std::ostream* out_strm)
	: log_streams(), severity(LOGGER_INFO)
{
	// attach the given ostream
	this->attach(out_strm);
}

// stream management functions
void Logger::attach(std::ostream* out_strm)
{
	// first make sure the out_strm points to a real (open) ostream and then
	//   add it to our list of streams
	if(out_strm!=nullptr && *out_strm) this->log_streams.push_back(out_strm);
}

void Logger::flush() const
{
	for (std::ostream* out_strm: this->log_streams) 
	{
		// make sure the stream is valid
		if (out_strm != nullptr && *out_strm) 
		{
			out_strm->flush();
		}
		else
		{
			// remove this stream from our vector
			_logErr(LOGGER_ERROR, "Error - invalid stream");
		}
	}
}

/*
* logging methods by severity, takes in the context string and a message to log
*/
void Logger::log(int severity, const std::string&ctxStr, const std::string& msg) const
{
	// first check the severity code
	if (severity <= this->severity) 
	{

		// append this message to our Logger ostreams
		for (std::ostream* out_strm : this->log_streams) 
		{
			// make sure the stream is valid
			if (out_strm != nullptr && (*out_strm)) 
			{
				*out_strm << msg << endl;
				out_strm->flush();
			}
			else
			{
				// remove this stream from our vector
				_logErr(LOGGER_ERROR, "Error - invalid stream");
			}
		}
	}
}
void Logger::trace(const std::string&ctxStr, const std::string& msg) const
{
	this->log(LOGGER_TRACE, ctxStr, msg);
}
void Logger::debug(const std::string&ctxStr, const std::string& msg) const
{
	this->log(LOGGER_DEBUG, ctxStr, msg);
}
void Logger::info(const std::string&ctxStr, const std::string& msg) const
{
	this->log(LOGGER_INFO, ctxStr, msg);
}
void Logger::warn(const std::string&ctxStr, const std::string& msg) const
{
	this->log(LOGGER_WARN, ctxStr, msg);
}
void Logger::error(const std::string&ctxStr, const std::string& msg) const
{
	this->log(LOGGER_ERROR, ctxStr, msg);
}

// gets and sets the severity for filtering messages
int  Logger::getSeverity(void) const
{
	return severity;
}
void Logger::setSeverity(int val)
{
	severity = val;
}

void Logger::_logErr(int severity, const std::string& msg) const 
{

	// first check the severity code
	if (severity <= this->severity)
	{
		// first print to stderr
		std::cerr << msg << endl;
		std::cerr.flush();

		// append this message to our Logger ostreams
		for (std::ostream* out_strm : this->log_streams)
		{
			// make sure the stream is valid
			if (out_strm != nullptr && *out_strm)
			{
				*out_strm << msg << endl;
				out_strm->flush();
			}
		}
	}
}