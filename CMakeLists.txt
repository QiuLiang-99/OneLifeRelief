cmake_minimum_required(VERSION 3.5)

project(OneLifeRelief VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:/Qt/QT/6.6.2/mingw_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
#添加sql数据库头
find_package(Qt6 REQUIRED COMPONENTS Sql)

include_directories(${CMAKE_SOURCE_DIR}/src)#添加头文件路径,搜索头文件时将会从此处作为顶格目录开始搜索

set(PROJECT_SOURCES
        main.cpp
)
file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/src/*.h)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OneLifeRelief
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${srcs} ${headers}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET OneLifeRelief APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(OneLifeRelief SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(OneLifeRelief
            ${PROJECT_SOURCES}
        )
    endif()
endif()
target_link_libraries(OneLifeRelief  PRIVATE Qt6::Sql)#添加sql数据库头
target_link_libraries(OneLifeRelief PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.OneLifeRelief)
endif()
set_target_properties(OneLifeRelief PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS OneLifeRelief
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OneLifeRelief)
endif()
