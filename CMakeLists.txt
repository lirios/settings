project(SystemPreferences)

cmake_minimum_required(VERSION 2.8.9)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Set version
set(SYSTEMPREFERENCES_VERSION_MAJOR 0)
set(SYSTEMPREFERENCES_VERSION_MINOR 1)
set(SYSTEMPREFERENCES_VERSION_PATCH 91)
set(SYSTEMPREFERENCES_VERSION_STRING "${SYSTEMPREFERENCES_VERSION_MAJOR}.${SYSTEMPREFERENCES_VERSION_MINOR}.${SYSTEMPREFERENCES_VERSION_PATCH}")

# Installation directories
include(GNUInstallDirs)

# Macro to print feature summary
include(FeatureSummary)

# Add custom uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

# Set up packaging
set(CPACK_PACKAGE_NAME hawaii-system-preferences)
set(CPACK_PACKAGE_VERSION ${SYSTEMPREFERENCES_VERSION_STRING})
set(CPACK_SYSTEM_NAME "generic")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SET_DESTDIR FALSE)
include(CPack)

# Build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden -Wall -std=c++0x")

# Assume release build by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "" FORCE)
endif()

# Disable debug output for release builds
if(CMAKE_BUILD_TYPE MATCHES "^[Rr]elease$")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# Include important features
include(GenerateExportHeader)

# Find Qt5
find_package(Qt5 5.2 REQUIRED COMPONENTS Configuration AccountsService LinguistTools)

# Find PolicyKit wrapper for Qt
find_package(PolkitQt-1 "0.103.0" REQUIRED)
if(NOT PolkitQt-1_FOUND)
    message(FATAL_ERROR "PolkitQt-1 module is required!")
endif()

# Subdirectories
add_subdirectory(data)
add_subdirectory(headers)
add_subdirectory(src)

# Display featute summary
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
