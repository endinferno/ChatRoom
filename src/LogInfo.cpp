/******************************************************
#
#      Filename: LogInfo.cpp
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file implements log system.
# File Encoding: UTF-8
#        Create: 2020-05-09 01:42:58
# Last Modified: 2020-05-24 17:55:38
 ******************************************************/

#include "../include/LogInfo.h"

LogInfo::LogInfo()
{
    this->logfile.open(LOG_FILE_LOCATION + getCurrentDateStr() + ".log", std::ios::ate);
}

LogInfo &LogInfo::GetInstance()
{
    static LogInfo log;
    return log;
}

void LogInfo::err(const std::string &str)
{
    this->outLine(getHeader("Error") + str);
}

void LogInfo::warn(const std::string &str)
{
    this->outLine(getHeader("Warning") + str);
}

void LogInfo::info(const std::string &str)
{
    this->outLine(getHeader("Info") + str);
}

LogInfo::~LogInfo()
{
    this->logfile.close();
}

void LogInfo::outLine(const std::string &str)
{
    this->logfile << str << "\n";
	this->logfile.flush();
}
