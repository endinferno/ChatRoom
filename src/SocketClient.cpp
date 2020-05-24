/******************************************************
#
#      Filename: SocketClient.cpp
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file implements client socket class.
# File Encoding: UTF-8
#        Create: 2020-05-09 01:15:54
# Last Modified: 2020-05-23 14:07:08
******************************************************/

#include "../include/SocketClient.h"

SocketClient::SocketClient()
{
    this->Init();
    this->Connect();
    // this->SetTimeout(3);
}

SocketClient::~SocketClient()
{
    close(this->sockfd);
}

// Init the client socket
void SocketClient::Init()
{
    // Create Client Socket
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->sockfd < 0)
    {
        err("Could not create socket.");
        exit(ERR_CODE);
    }
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = inet_addr(REMOTE_IP_ADDRESS);
    this->serv_addr.sin_port = htons(REMOTE_PORT);
}

// Connect the server
void SocketClient::Connect()
{
    int ret = connect(this->sockfd,
                      (struct sockaddr *) &this->serv_addr,
                      sizeof(this->serv_addr));
    if (ret < 0)
    {
        err("Connect Failed");
        exit(ERR_CODE);
    }
}

// Set Non Block
void SocketClient::SetNonBlock()
{
    // 1 for nonblock, 0 for block
    int b_on = 1;
    ioctl(this->sockfd, FIONBIO, &b_on);
}

// Set Time Out
void SocketClient::SetTimeout(const int sec)
{
    struct timeval tv;
    tv.tv_sec = sec;
    tv.tv_usec = 0;
    setsockopt(this->sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    setsockopt(this->sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
}

// Read Data
std::string SocketClient::Recv()
{
    char recvBuf[1024] = {0};
    int len = 0;
    while ((len = recv(this->sockfd, recvBuf, sizeof(recvBuf) - 1, 0)) > 0)
        recvBuf[len] = '\0';
    if (len < 0)
        if (errno == EINTR)
            err("Read Error");
    return std::string(recvBuf);
}

// Send Data
void SocketClient::Send(const std::string &str)
{
    if (str.size() != 0)
    {
        int ret = send(this->sockfd, str.c_str(), str.size(), 0);
        if (ret < 0)
            if (errno == EINTR)
                err("Send Error");
    }
}
