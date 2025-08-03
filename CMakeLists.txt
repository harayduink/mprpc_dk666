# 设置cmake的最低版本和项目名称
cmake_minimum_required(VERSION 3.0)

project(mprpc)

# 设置调试信息
set(CMAKE_BUILD_TYPE "Debug")

# 设置项目可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置项目库文件的输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 设置项目编译头文件的搜索路径 -I
include_directories(${PROJECT_SOURCE_DIR}/src/include)
# include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/example)
find_package(Protobuf)
# 设置项目库文件的搜索路径 -L
link_directories(${PROJECT_SOURCE_DIR}/lib)
# find_package(Protobuf REQUIRED)
# find_package(gRPC REQUIRED)   
# src包含mprpc框架所有的相关代码
add_subdirectory(src)
# example包含mprpc框架的使用代码
add_subdirectory(example)
