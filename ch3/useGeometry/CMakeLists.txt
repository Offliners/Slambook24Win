cmake_minimum_required(VERSION 2.8)
project(geometry)

# 添加Eigen標頭檔文件
include_directories("C:\\MinGW\\include\\Eigen")

add_executable(eigenGeometry eigenGeometry.cpp)