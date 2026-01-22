# Ubuntu20的apt默认的cmake版本为3.16.3
cmake_minimum_required(VERSION 3.20.0)

project(inc_bin
    DESCRIPTION "inc bin"
    LANGUAGES C CXX ASM
)

# 追加编译选项
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-pie")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-pie")

# 追加链接选项
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -no-pie")

add_library(inc_bin SHARED)
target_sources(inc_bin PRIVATE
    source/blob.S
)
target_include_directories(inc_bin PUBLIC
    .
)
set_target_properties(inc_bin PROPERTIES LINKER_LANGUAGE CXX)


add_executable(test_main)
target_sources(test_main PRIVATE source/test_main.cc)
target_link_libraries(test_main PRIVATE 
    inc_bin
    dl
)
