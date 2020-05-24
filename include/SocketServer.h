/******************************************************
#
#      Filename: include/SocketServer.h
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file used for server
# File Encoding: UTF-8
#        Create: 2020-05-22 20:25:47
# Last Modified: 2020-05-23 12:07:54
******************************************************/

#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include "../include/Config.h"
#include "../include/LogInfo.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <thread>
#include <unistd.h>
#include <vector>

class SocketServer
{
  public:
    SocketServer();
    void Listen();
    ~SocketServer();

  private:
    void Init();
    void BindAndListen();
    static void ProcessClient(int);

  private:
    int listenfd;
    struct sockaddr_in serv_addr;
    std::vector<int> connfd_vec;
};

#endif // SocketServer.h
