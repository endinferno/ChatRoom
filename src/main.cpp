/******************************************************
#
#      Filename: src/main.cpp
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: main Func
# File Encoding: UTF-8
#        Create: 2020-05-09 01:04:17
# Last Modified: 2020-05-24 17:49:31
 ******************************************************/

#include "SocketServer.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	SocketServer server;
	server.Listen();
	return 0;
}
