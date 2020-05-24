/******************************************************
#
#      Filename: SocketClient.h
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file is client socket class.
# File Encoding: UTF-8
#        Create: 2020-05-09 01:03:41
# Last Modified: 2020-05-22 20:32:38
******************************************************/

#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include "../include/Config.h"
#include "../include/LogInfo.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

class SocketClient
{
  public:
    SocketClient();
    std::string Recv();
    void Send(const std::string &);
    ~SocketClient();

  private:
    void Init();
    void Connect();
    void SetNonBlock();
    void SetTimeout(const int);

  private:
    struct sockaddr_in serv_addr;
    int sockfd;
};

#endif // SocketClient.h
