set(HEADERS
    PreferencesModule
    PreferencesModulePlugin
    SystemPreferencesExport
)

install(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Hawaii/SystemPreferences)
