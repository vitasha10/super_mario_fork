cmake_minimum_required(VERSION 3.2...3.27.5)

project(super_mario)

SET(CMAKE_CXX_FLAGS "-finput-charset=utf-8 -fexec-charset=utf-8")

option(BUILD_QT_UI "Build Qt-based UI" OFF)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

if(MINGW)
        target_sources(${PROJECT_NAME} PRIVATE mingw_compat.cpp)
        target_compile_options(${PROJECT_NAME} PRIVATE "-include" "mingw_compat.hpp")
endif()

if(BUILD_QT_UI)
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTORCC ON)
        set(CMAKE_AUTOUIC ON)

        find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
        find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

        target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
        target_compile_definitions(${PROJECT_NAME} PRIVATE BIV_USE_QT_UI)
endif()

add_subdirectory(os_controls)
add_subdirectory(controller)
add_subdirectory(levels)
add_subdirectory(model)
add_subdirectory(objects)
add_subdirectory(ui)
