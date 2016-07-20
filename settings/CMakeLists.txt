include(ECMPackageConfigHelpers)
include(ECMSetupVersion)

ecm_setup_version(${PROJECT_VERSION} VARIABLE_PREFIX HAWAII_SYSTEM_PREFERENCES
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/HawaiiSystemSettingsConfigVersion.cmake")

set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/HawaiiSystemSettings")

ecm_configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/HawaiiSystemSettingsConfig.cmake.in"
                                  "${CMAKE_CURRENT_BINARY_DIR}/HawaiiSystemSettingsConfig.cmake"
                                  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
                                  )

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/HawaiiSystemSettingsConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/HawaiiSystemSettingsConfigVersion.cmake"
              "${CMAKE_CURRENT_SOURCE_DIR}/HawaiiSystemSettingsMacros.cmake"
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
)

add_executable(hawaii-settings ${SOURCES} ${QM_FILES})
target_link_libraries(hawaii-settings
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::QuickControls2)
                      
#                      ${POLKITQT-1_GUI_LIBRARY}

install(TARGETS hawaii-settings
    DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-settings/translations)

hawaii_translate_desktop(DESKTOP_FILE
                         SOURCES org.hawaiios.Settings.desktop.in)
add_custom_target(hawaii-settings_translations ALL DEPENDS ${DESKTOP_FILE})
install(FILES ${DESKTOP_FILE}
        DESTINATION ${KDE_INSTALL_APPDIR}
        COMPONENT "Runtime")
