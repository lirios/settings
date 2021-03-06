cmake_minimum_required(VERSION 3.10.0)

project("Settings"
    VERSION "0.9.0"
    DESCRIPTION "Settings application"
    LANGUAGES CXX C
)

## Shared macros and functions:
if(NOT LIRI_LOCAL_ECM)
    find_package(LiriCMakeShared "1.0.0" REQUIRED NO_MODULE)
    list(APPEND CMAKE_MODULE_PATH "${LCS_MODULE_PATH}")
endif()

## Set minimum versions required:
set(QT_MIN_VERSION "5.10.0")

## Add some paths to check for CMake modules:
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

## Liri specific setup common for all modules:
include(LiriSetup)

## Find Qt 5:
find_package(Qt5 "${QT_MIN_VERSION}"
    CONFIG REQUIRED
    COMPONENTS
        Core
        Concurrent
        DBus
        Xml
        Gui
        Widgets
        Qml
        Quick
        QuickControls2
        LinguistTools
)

## Add subdirectories:
add_subdirectory(src/app)
add_subdirectory(src/imports/settings)
add_subdirectory(src/modules/appearance)
add_subdirectory(src/modules/background)
add_subdirectory(src/modules/display)
add_subdirectory(src/modules/info)
add_subdirectory(src/modules/keyboard)
add_subdirectory(src/modules/locale)
add_subdirectory(src/modules/users)
