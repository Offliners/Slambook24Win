# 宣告要求的cmake最低版本
cmake_minimum_required(VERSION 2.8)

# 宣告一個cmake專案
project(HelloSLAM)

# 增加一個可執行程式
add_executable(helloSLAM helloSLAM.cpp)

# 添加hello庫
add_library(hello libHelloSLAM.cpp)

# 共享庫
add_library(hello_shared SHARED libHelloSLAM.cpp)

# 添加可執行程序調用hello庫函式
add_executable(useHello useHello.cpp)

# 將庫文件連結到可執行程序上
target_link_libraries(useHello hello_shared)
