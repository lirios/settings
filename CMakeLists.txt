cmake_minimum_required(VERSION 3.19)

project("Settings"
    VERSION "0.9.0"
    DESCRIPTION "Settings application"
    LANGUAGES CXX C
)

## Only build on the appropriate platforms.
if(NOT (UNIX OR NOT CMAKE_SYSTEM_NAME MATCHES "Android"))
    message(NOTICE "Skipping the build as the condition \"UNIX OR NOT Android\" is not met.")
    return()
endif()

## Add some paths to check for CMake modules:
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

## Macros and functions:
include(LiriAddSettingsModule)

## ECM:
find_package(ECM 5.245.0 REQUIRED NO_MODULE)
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

## Installation directories:
include(KDEInstallDirs)

## Compiler settings:
set(KDE_SKIP_NULLPTR_WARNINGS_SETTINGS TRUE)
include(KDECompilerSettings NO_POLICY_SCOPE)

## Enable keywords such as emit:
# TODO: Replace keywords such as emit with Q_EMIT
remove_definitions(-DQT_NO_KEYWORDS)

## CMake settings:
include(KDECMakeSettings)

## QML module:
include(ECMQmlModule)

## Disable use of C++ API deprecated in Qt 5.15
add_compile_definitions(QT_DISABLE_DEPRECATED_UP_TO=0x050F00)

## QML import path:
if(NOT QML_IMPORT_PATH)
    set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/bin CACHE STRING "" FORCE)
endif()

## Find Qt:
find_package(Qt6 "6.6.0"
    REQUIRED
    COMPONENTS
        Core
        Concurrent
        DBus
        Xml
        Gui
        Widgets
        Qml
        QmlIntegration
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
add_subdirectory(src/modules/updates)
add_subdirectory(src/modules/users)
