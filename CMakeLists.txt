cmake_minimum_required(VERSION 3.25)
project(CRM)

set(CMAKE_CXX_STANDARD 11)

add_executable(CRM main.cpp src/workerManager.cpp
                            src/employee.cpp
                            src/worker.cpp
                            src/boss.cpp src/manager.cpp)

include_directories(include)
