project(HawaiiSystemPreferences)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

# Silence CMake warnings
if(POLICY CMP0063)
    cmake_policy(SET CMP0063 NEW)
endif()

# Set version
set(PROJECT_VERSION "0.6.90")
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_SOVERSION 0)

# Set up packaging
set(CPACK_PACKAGE_NAME "hawaii-system-preferences")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SET_DESTDIR FALSE)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES "/build/;/.git;/.tx/;~$;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

# Assume release build by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "" FORCE)
endif()

# Build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden -Wall -Wextra -Wno-unused-parameter -std=c++11")

# ECM
find_package(ECM 1.4.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

# Find libhawaii
set(REQUIRED_HAWAII_VERSION "0.6.90")
find_package(Hawaii ${REQUIRED_HAWAII_VERSION} REQUIRED)

# Add custom uninstall target
if ("${ECM_VERSION}" VERSION_LESS "1.7.0")
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)
    add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
endif()

# Macros
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)

# Include our macros
include(${CMAKE_SOURCE_DIR}/settings/HawaiiSystemPreferencesMacros.cmake)

# Find Qt5
set(REQUIRED_QT_VERSION "5.2.0")
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED COMPONENTS
             Core
             Gui
             Widgets
             Qml
             Quick
             LinguistTools)

# Find PolicyKit wrapper for Qt
find_package(PolkitQt5-1 "0.103.0" REQUIRED)

# Find KScreen
find_package(KF5Screen "5.2.0")

# Subdirectories
add_subdirectory(data)
add_subdirectory(declarative)
add_subdirectory(modules)
add_subdirectory(settings)
add_subdirectory(shells)

# Translation custom target
add_custom_target(update-translations DEPENDS
    update-translations-app
    update-translations-background
    update-translations-desktop
    update-translations-keyboard
    update-translations-network
)

# Display featute summary
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
