cmake_minimum_required(VERSION 3.5)

project(OneLifeRelief VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CLANG_TIDY_COMMAND clang-tidy -header-filter=^${PROJECT_ROOT_DIR}/src/*)
set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_COMMAND})#设置clang-tidy检查所有的文件

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)#查找qt的widgets库
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)#添加sql数据库头

set(PROJECT_SOURCES
        main.cpp
)
file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/src/*.h)#自动编译所有src内的源文件和头文件
qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${srcs} ${headers}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)#添加头文件路径,搜索头文件时将会从此处作为顶格目录开始搜索
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Sql)#添加sql数据库头
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)#将先前查到到的库的头文件链接到项目

add_library(QxOrm SHARED IMPORTED)#导QxOrm库
set(QxOrm_dir "D:/Qt/QxOrm/QxOrm-1.4.9")#设置QxOrm库的路径
# 检查目标平台
if(WIN32)
    # 针对Windows的配置
    set_target_properties(QxOrm PROPERTIES
        IMPORTED_LOCATION             ${QxOrm_dir}/lib/libQxOrmd.dll
        IMPORTED_IMPLIB               ${QxOrm_dir}/lib/libQxOrmd.dll.a
        INTERFACE_INCLUDE_DIRECTORIES ${QxOrm_dir}/include
    )#设置QxOrm库的路径
    file(COPY  ${QxOrm_dir}/lib/libQxOrmd.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
elseif(ANDROID)
    # 针对Android的配置
    set_target_properties(QxOrm PROPERTIES
        IMPORTED_LOCATION             ${QxOrm_dir}/lib/libQxOrmd.so
        #IMPORTED_IMPLIB               ${QxOrm_dir}/lib/libQxOrmd.dll.a
        INTERFACE_INCLUDE_DIRECTORIES ${QxOrm_dir}/include
    )#设置QxOrm库的路径
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE QxOrm)#将QxOrm库链接到项目

set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    #WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
qt_finalize_executable(${PROJECT_NAME})