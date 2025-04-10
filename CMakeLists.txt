﻿
cmake_minimum_required(VERSION 3.5)

project(qtandroidcls VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB QTANDROIDCLS_PROJECT_SOURCES
    "./src/*.h"
    "./src/*.cpp"
    "./src/*.ui"
    "./src/*/*.h"
    "./src/*/*.cpp"
    "./src/*/*.ui"
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_library(${PROJECT_NAME} SHARED ${QTANDROIDCLS_PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)


ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND python3 "${CMAKE_SOURCE_DIR}/script/output-cpplib.py" android)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS AndroidExtras)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS AndroidExtras)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::AndroidExtras)
set(ANDROID_ABI armeabi-v7a)
set(ANDROID_NATIVE_API_LEVEL 21)

add_definitions(-D_HAS_STD_BYTE=0)

