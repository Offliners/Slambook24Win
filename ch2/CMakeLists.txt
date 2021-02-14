# 聲明要求的cmake最低版本
cmake_minimum_required(VERSION 2.8)                                                                  

# 聲明這是一個cmake工程
project(HelloSLAM)

# 設置編譯模式
set(CMAKE_BUILD_TYPE "Debug")

add_executable(helloSLAM helloSLAM.cpp)

# 添加工具庫
add_library(hello libHelloSLAM.cpp)
# 添加共享工具庫
add_library(hello_shared SHARED libHelloSLAM.cpp)

add_executable(useHello useHello.cpp)
# 將工具庫文件連接到可執行程序上
target_link_libraries(useHello hello_shared)
