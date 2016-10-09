include(ECMSetupVersion)
include(CMakePackageConfigHelpers)

ecm_setup_version(${PROJECT_VERSION} VARIABLE_PREFIX LIRI_SETTINGS
                  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/LiriSettingsConfigVersion.cmake")

set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/LiriSettings")

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/LiriSettingsConfig.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/LiriSettingsConfig.cmake"
                              INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/LiriSettingsConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/LiriSettingsConfigVersion.cmake"
              "${CMAKE_CURRENT_SOURCE_DIR}/LiriSettingsMacros.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)
