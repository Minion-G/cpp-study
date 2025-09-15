cmake_minimum_required(VERSION 3.29)
project(net_tools)

set(CMAKE_CXX_STANDARD 17)

add_library(net_tools
        src/sock_address.cpp
        include/net_tools/sock_address.hpp
)

target_include_directories(net_tools
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(net_tools PUBLIC cxx_std_17)