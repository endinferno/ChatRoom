/******************************************************
#
#      Filename: LogInfo.h
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file used for log system.
# File Encoding: UTF-8
#        Create: 2020-05-09 01:39:30
# Last Modified: 2020-05-22 22:50:22
 ******************************************************/

#ifndef LOGINFO_H
#define LOGINFO_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Config.h"

class LogInfo
{
  public:
    static LogInfo &GetInstance();
    void err(const std::string &);
    void warn(const std::string &);
    void info(const std::string &);

  private:
    LogInfo();
    LogInfo(const LogInfo &);
    LogInfo &operator=(const LogInfo &);
    void outLine(const std::string &);
    ~LogInfo();
    std::ofstream logfile;
};

static void err(const std::string &str)
{
    LogInfo::GetInstance().err(str);
}

static void info(const std::string &str)
{
    LogInfo::GetInstance().info(str);
}

static void warning(const std::string &str)
{
    LogInfo::GetInstance().warn(str);
}

static std::string getCurrentDateStr()
{
    time_t t = time(NULL);
    char ch[64] = {0};
    strftime(ch, sizeof(ch) - 1, "%Y-%m-%d", localtime(&t)); //年-月-日
    return ch;
}

static std::string getCurrentTimeStr()
{
    time_t t = time(NULL);
    char ch[64] = {0};
    strftime(ch, sizeof(ch) - 1, "%H:%M:%S", localtime(&t)); //年-月-日
    return ch;
}

static std::string getHeader(const std::string &type_str)
{
    char buf[64] = {0};
    sprintf(buf, "[%s]%9s :", getCurrentTimeStr().c_str(), type_str.c_str());
    return std::string(buf);
}

#endif // LogInfo.h
