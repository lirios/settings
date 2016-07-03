include(ECMPackageConfigHelpers)
include(ECMSetupVersion)

ecm_setup_version(${PROJECT_VERSION} VARIABLE_PREFIX HAWAII_SYSTEM_PREFERENCES
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/HawaiiSystemPreferencesConfigVersion.cmake")

set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/HawaiiSystemPreferences")

ecm_configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/HawaiiSystemPreferencesConfig.cmake.in"
                                  "${CMAKE_CURRENT_BINARY_DIR}/HawaiiSystemPreferencesConfig.cmake"
                                  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
                                  )

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/HawaiiSystemPreferencesConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/HawaiiSystemPreferencesConfigVersion.cmake"
              "${CMAKE_CURRENT_SOURCE_DIR}/HawaiiSystemPreferencesMacros.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

##############################################################################

include_directories(
    ${POLKITQT-1_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${CMAKE_SOURCE_DIR}/src/lib
)

# Create the cmakedirs.h header file
configure_file(cmakedirs.h.in ${CMAKE_CURRENT_BINARY_DIR}/cmakedirs.h)

# Create the config.h header file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY
)

set(SOURCES
    main.cpp
    plugin.cpp
    pluginmanager.cpp
    pluginsmodel.cpp
    xdgdesktopfile.cpp
)

add_executable(hawaii-system-preferences ${SOURCES} ${QM_FILES})
target_link_libraries(hawaii-system-preferences
                      Qt5::Qml
                      Qt5::Quick
)
#                      ${POLKITQT-1_GUI_LIBRARY}

install(TARGETS hawaii-system-preferences
    DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/translations)

hawaii_translate_desktop(DESKTOP_FILE
                         SOURCES org.hawaiios.SystemPreferences.desktop.in)
add_custom_target(hawaii-system-preferences_translations ALL DEPENDS ${DESKTOP_FILE})
install(FILES ${DESKTOP_FILE}
        DESTINATION ${KDE_INSTALL_APPDIR}
        COMPONENT "Runtime")
