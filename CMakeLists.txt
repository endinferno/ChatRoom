cmake_minimum_required(VERSION 3.8)
project(client)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig)
# pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(include)
include_directories(/usr/local/mysql/include)
# include_directories(${GTKMM_INCLUDE_DIRS})

# link_directories(${GTKMM_LIBRARY_DIRS})
link_directories(/usr/local/mysql/lib)
link_libraries(mysqlclient)

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

add_executable(client ./src/main.cpp ./src/Config.cpp ./src/LogInfo.cpp ./src/SocketClient.cpp ./src/Client.cpp)

target_link_libraries(client mysqlclient)
# target_link_libraries(client ${GTKMM_LIBRARIES})
