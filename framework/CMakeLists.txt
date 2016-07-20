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
