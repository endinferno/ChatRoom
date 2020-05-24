/******************************************************
#
#      Filename: src/DataBase.cpp
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file implements DataBase.
# File Encoding: UTF-8
#        Create: 2020-05-11 22:42:15
# Last Modified: 2020-05-12 14:22:38
******************************************************/

#include "../include/DataBase.h"

Database::Database()
    : conn(nullptr)
{
    this->Init();
    this->Connect();
}

Database::~Database()
{
    if (this->conn != nullptr)
    {
        mysql_close(this->conn);
        this->conn = nullptr;
    }
}

void Database::InsertChat(json &chat)
{
    std::string query = this->GetInsertQueryString("test", chat);
	unsigned long affected_row = this->Insert(query);
	if (affected_row != 1)
		warning("MySQL Insert Affect Number Error");
}

json Database::FetchChat(const std::string &query)
{
    json dataPack;

    this->Query(query);
    MYSQL_ROW sql_row;
    MYSQL_RES *result = mysql_store_result(this->conn);
    if (result == nullptr)
    {
        err("MySQL Get Data Error " + std::string(mysql_error(this->conn)));
        return dataPack;
    }
    // Get Field Name
    // json fieldName;
    // MYSQL_FIELD *field;
    // while ((field = mysql_fetch_field(result)))
    //     fieldName.push_back(field->name);
    // dataPack.push_back(fieldName);
    // Get Data
    while ((sql_row = mysql_fetch_row(result)))
    {
        json part;
        for (int i = 0; i < mysql_num_fields(result); i++)
        {
            if (sql_row[i])
                part.push_back(sql_row[i]);
        }
        dataPack.push_back(part);
    }
    mysql_free_result(result);
    return dataPack;
}

void Database::Init()
{
    this->conn = mysql_init(nullptr);
    if (this->conn == nullptr)
    {
        err("MySQL Init Error " + std::string(mysql_error(this->conn)));
        exit(ERR_CODE);
    }
}

void Database::Connect()
{
    MYSQL *ret = mysql_real_connect(this->conn,
                                    DATABASE_SERVER_IP,
                                    DATABASE_USER,
                                    DATABASE_PASSWORD,
                                    DATABASE_NAME,
                                    0, nullptr, 0);
    if (ret == nullptr)
    {
        err("MySQL Connect Error " + std::string(mysql_error(ret)));
        exit(ERR_CODE);
    }
}

void Database::Query(const std::string &query)
{
    int ret = mysql_query(this->conn, query.c_str());
    if (ret != 0)
    {
        err("MySQL Query Error " + std::string(mysql_error(this->conn)));
        exit(ERR_CODE);
    }
}

unsigned long Database::Insert(const std::string &query)
{
    int ret = mysql_query(this->conn, query.c_str());
    if (ret != 0)
    {
        err("MySQL Insert Error " + std::string(mysql_error(this->conn)));
        return 0;
    }
    else
        return (unsigned long) mysql_affected_rows(this->conn);
}

std::string Database::GetInsertQueryString(const std::string &databaseName, const json &dataPack)
{
    int fromUserID = dataPack["fromUserID"].get<int>();
    int targetUserID = dataPack["targetUserID"].get<int>();
    std::string content = dataPack["content"].get<std::string>();
    int chatTime = dataPack["charAt"].get<int>();
    std::string chatAt = stamp_to_standard(chatTime);
    std::string insert_query = "INSERT INTO " + databaseName +
                               " (fromUserID, targetUserID, content, chatAt) " +
                               " VALUES " +
                               "(" + std::to_string(fromUserID) + "," +
                               std::to_string(targetUserID) + "," +
                               "'" + content + "'," +
                               "'" + chatAt + "'" + ");";
    return insert_query;
}
