cmake_minimum_required(VERSION 3.20)

project(SelfBalancingTree LANGUAGES CXX)


set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

add_executable(main
	src/main.cpp
	src/SBT_class.cpp
)