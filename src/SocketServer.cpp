/******************************************************
#
#      Filename: src/SocketServer.cpp
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: This file used for implementing server
# File Encoding: UTF-8
#        Create: 2020-05-22 20:25:46
# Last Modified: 2020-05-24 17:56:08
******************************************************/

#include "../include/SocketServer.h"

SocketServer::SocketServer()
{
    this->Init();
    this->BindAndListen();
}

SocketServer::~SocketServer()
{
}

void SocketServer::Init()
{
    this->listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->listenfd < 0)
    {
        err("Could not Create Socket.");
        exit(ERR_CODE);
    }
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->serv_addr.sin_port = htons(REMOTE_PORT);
}

void SocketServer::BindAndListen()
{
    int ret = bind(this->listenfd, (struct sockaddr *) &this->serv_addr, sizeof(this->serv_addr));
    if (ret < 0)
    {
        err("Bind Error");
        exit(1);
    }
    ret = listen(this->listenfd, 10);
    if (ret < 0)
    {
        err("Listen Error");
        exit(1);
    }
}

void SocketServer::ProcessClient(int connfd)
{
    std::ostringstream oss;
    // Print Thread Client Connect Information
    oss << "Client Connect : " << std::this_thread::get_id() << "\n";
    info(oss.str());

    while (true)
    {
        char buff[4096];
        int n;
        n = recv(connfd, buff, 4095, 0);
        buff[n] = '\0';
        printf("recv msg from client: %s\n", buff);
		if (strcmp(buff, "exit") == 0)
			break;

        // time_t ticks = time(NULL);
        // char sendBuff[1025];
        // snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        // write(connfd, sendBuff, strlen(sendBuff));
    }
    close(connfd);

    // Print Thread Client Stop Information
    oss.str("");
    oss << "Thread Client : " << std::this_thread::get_id() << " Over.\n";
    info(oss.str());
}

void SocketServer::Listen()
{
    while (true)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int connfd = accept(listenfd,
                            (struct sockaddr *) &client_addr,
                            &client_addr_size);
        this->connfd_vec.push_back(connfd);
        std::thread conn_thread(ProcessClient, connfd);
        conn_thread.detach();
    }
    // for (int connfd : this->connfd_vec)
    // close(connfd);
}
