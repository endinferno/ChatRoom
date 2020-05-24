/******************************************************
#
#      Filename: src/Client.cpp
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file implements Client Class.
# File Encoding: UTF-8
#        Create: 2020-05-11 14:56:49
# Last Modified: 2020-05-12 13:57:29
******************************************************/

#include "../include/Client.h"

extern bool userIDList[1000];

Client::Client()
{
    this->userID = getUniqueID();
    if (this->userID == (unsigned long long) (-1))
        err("Fail to Setting User ID");
}

Client::~Client()
{
    userIDList[this->userID] = false;
}

void Client::SendMessage(const int targetID, const std::string &message)
{
    json dataPack;
    dataPack["targetID"] = targetID;
    dataPack["content"] = message;
    SendData(COMMUNICATE, dataPack);
}

bool Client::Login(std::string account, std::string password)
{
    return true;
}

// Send Data
// Data Type: 1(communicate)
// targetID, content, timeStamp
void Client::SendData(const size_t dataType, json &dataPack)
{
    dataPack["timeStamp"] = getTimeStamp();
    dataPack["messageType"] = dataType;
    std::string str = dataPack.dump();
    this->socket.Send(str);
}

json Client::RecvData()
{
    std::string message = this->socket.Recv();
    return json::parse(message);
}
