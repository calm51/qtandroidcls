cmake_minimum_required(VERSION 3.5)

project(qtandroiddemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    resource.qrc
)

set(ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt5_add_resources(QT_RESOURCE_FILES ${PROJECT_DIR}/resource.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#    ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    set(ANDROID_MIN_SDK_VERSION 21)
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR ${PROJECT_DIR}/android)
    #    set(ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android CACHE INTERNAL "")
    #    if (ANDROID_ABI STREQUAL "armeabi-v7a")
    #        set(ANDROID_EXTRA_LIBS
    #            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
    #            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()



# =============================================

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS AndroidExtras)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS AndroidExtras)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::AndroidExtras)
add_definitions(-D_HAS_STD_BYTE=0)

# =============================================

set(qtandroidcls_include ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
include_directories(${qtandroidcls_include})

set(qtandroidcls_platform "android")
set(qtandroidcls_lib_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${qtandroidcls_platform}/qtandroidcls)
set(qtandroidcls_lib ${qtandroidcls_lib_dir}/libqtandroidcls_armeabi-v7a.so)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${qtandroidcls_lib}" "${CMAKE_CURRENT_BINARY_DIR}/android-build/libs/${ANDROID_ABI}/libqtandroidcls_armeabi-v7a.so")
#target_link_libraries(${PROJECT_NAME} PRIVATE ${qtandroidcls_lib})
target_link_directories(${PROJECT_NAME} PRIVATE ${qtandroidcls_lib_dir})
target_link_libraries(${PROJECT_NAME} PRIVATE "qtandroidcls_armeabi-v7a")


# =============================================





