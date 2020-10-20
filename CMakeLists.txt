cmake_minimum_required(VERSION 3.15)
project(MARKET_MANAGER)

set(CMAKE_CXX_STANDARD 14)

add_executable(MARKET_MANAGER main.cpp menu.h market.cpp market.h product.cpp product.h stock.cpp stock.h menu.cpp)