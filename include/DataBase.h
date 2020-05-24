/******************************************************
#
#      Filename: include/DataBase.h
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file used for connecting database.
# File Encoding: UTF-8
#        Create: 2020-05-11 22:42:09
# Last Modified: 2020-05-12 14:22:40
******************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include "../include/Config.h"
#include "../include/LogInfo.h"
#include "../include/nlohmann/json.hpp"
#include <array>
#include <cstdio>
#include <mysql.h>
using json = nlohmann::json;
#include <string>
// Get Result Field Number
// unsigned int num_fields = mysql_num_fields(result);

class Database
{
  public:
    Database();
    void InsertChat(json &);
    json FetchChat(const std::string &);
    ~Database();

  private:
    void Init();
    void Connect();
    void Query(const std::string &);
    // parameter: the query sentence
    // return: the number of rows which are affected
    unsigned long Insert(const std::string &);
    std::string GetInsertQueryString(const std::string &, const json &);

    MYSQL *conn;
};

static std::string stamp_to_standard(int stampTime)
{
    time_t tick = (time_t) stampTime;
    struct tm tim;
    char s[50];

    tim = *localtime(&tick);
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tim);
	return std::string(s);
}

#endif // DataBase.h
