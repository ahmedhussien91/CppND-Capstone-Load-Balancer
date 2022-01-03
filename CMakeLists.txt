cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17 -DDEBUG)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(LoadBalancer)

add_executable(load_balancer src/load_balancer/main.cpp src/load_balancer/requests.cpp src/load_balancer/nodes.cpp)
add_executable(user_sim src/request_sim/main.cpp src/request_sim/request.cpp)
add_executable(work_nodes src/work_nodes/main.cpp src/work_nodes/node.cpp)
