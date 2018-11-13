cmake_minimum_required(VERSION 3.12)
project(SPL_ass1)

set(CMAKE_CXX_STANDARD 11)

add_executable(SPL_ass1 src/Main.cpp src/Dish.cpp include/Dish.h src/Action.cpp include/Action.h src/Table.cpp include/Table.h src/Customer.cpp include/Customer.h src/Restaurant.cpp include/Restaurant.h)