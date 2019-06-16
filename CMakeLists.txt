# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (FSSE)

find_package (openssl)

# 版本号.
set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories ("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("/usr/local/Cellar/openssl/1.0.2s/include")

link_directories ("/usr/local/Cellar/openssl/1.0.2s/lib")

# 指定生成目标
add_executable (Demo 
  main.cpp
)