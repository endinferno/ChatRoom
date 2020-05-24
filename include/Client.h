/******************************************************
#
#      Filename: include/Client.h
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file used for Client Class.
# File Encoding: UTF-8
#        Create: 2020-05-11 14:56:39
# Last Modified: 2020-05-12 13:58:31
******************************************************/

#ifndef CLIENT_H
#define CLIENT_H

#include "../include/SocketClient.h"
#include "../include/nlohmann/json.hpp"
#include <ctime>
using json = nlohmann::json;

class Client
{
  public:
    Client();
    void SendMessage(const int, const std::string &);
    bool Login(std::string, std::string);
    ~Client();

  private:
    json RecvData();
    void SendData(const size_t, json &);

    unsigned long long userID;
    SocketClient socket;

  private:
    static const size_t COMMUNICATE = 1;
};

static bool userIDList[1000] = {false};

// Used for Assigning ID
// TODO: When you use userIDList, the userIDList should be locked
static unsigned long long getUniqueID()
{
    for (int i = 0; i < 1000; ++i)
    {
        if (userIDList[i] == false)
        {
            userIDList[i] = true;
            return (unsigned long long) i;
        }
    }
    return (unsigned long long) (-1);
}

static std::time_t getTimeStamp()
{
    std::time_t currentTimeStamp = time(NULL);
    return currentTimeStamp;
}

#endif // client.h
