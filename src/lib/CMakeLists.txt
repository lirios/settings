include_directories(${CMAKE_SOURCE_DIR}/headers)

# Sources
set(SOURCES
    preferencesmodule.cpp
    preferencesmoduleplugin.cpp
)

# Headers
set(HEADERS
    preferencesmodule.h
    preferencesmoduleplugin.h
    ${CMAKE_CURRENT_BINARY_DIR}/systempreferences_export.h
)

# Add library
add_compiler_export_flags()
add_library(HawaiiSystemPreferences SHARED ${SOURCES})
generate_export_header(HawaiiSystemPreferences
    BASE_NAME systempreferences
    DEPRECATED_MACRO_NAME HAWAII_SYSTEM_PREFERENCES_DEPRECATED
)
qt5_use_modules(HawaiiSystemPreferences Widgets)
set_target_properties(HawaiiSystemPreferences PROPERTIES
    VERSION ${SYSTEMPREFERENCES_VERSION_STRING}
    SOVERSION ${SYSTEMPREFERENCES_VERSION_MAJOR}.${SYSTEMPREFERENCES_VERSION_MINOR}.${SYSTEMPREFERENCES_VERSION_PATCH})

# Install files
install(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Hawaii/SystemPreferences)
install(TARGETS HawaiiSystemPreferences LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR})
