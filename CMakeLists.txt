cmake_minimum_required(VERSION 3.25)
project(drq CXX)

set(CMAKE_CXX_STANDARD  11)
# 设置编译选项
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# 添加源文件目录
aux_source_directory(include SOURCE_FILES)
aux_source_directory(test SOURCE_FILES)
#定义两个变量，表示头文件路径和库路径
find_package(OpenSSL REQUIRED)
# 显示的包含头文件
include_directories(include)

if(OPENSSL_FOUND)
    # 添加 libeTPSS.a 静态库
    add_library(eTPSS STATIC IMPORTED)
    set_property(TARGET eTPSS PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libeTPSS.a)

    add_executable(${PROJECT_NAME} ${SOURCE_FILES})

    add_executable(drq_test ${SOURCE_FILES})

    target_include_directories(${PROJECT_NAME} PUBLIC include)
    target_include_directories(drq_test PUBLIC include)
    # 链接 OpenSSL 库
    target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto eTPSS)
    target_link_libraries(drq_test OpenSSL::SSL OpenSSL::Crypto eTPSS)

endif (OPENSSL_FOUND)