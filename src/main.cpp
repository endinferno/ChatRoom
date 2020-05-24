/******************************************************
#
#      Filename: src/main.cpp
#
#        Author: endinferno - censhaofeng@buaa.edu.cn
#   Description: main Func
# File Encoding: UTF-8
#        Create: 2020-05-09 01:04:17
# Last Modified: 2020-05-24 17:35:18
 ******************************************************/

#include "SocketClient.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    SocketClient client;
    std::string str;
    while (true)
    {
        std::cin >> str;
        client.Send(str);
        if (str == "exit")
            break;
        // std::string temp = client.Recv();
        // std::cout << "Return Information " << temp << std::endl;
    }
    // std::string str = client.Recv();
    // std::cout << str << std::endl;
    return 0;
}
