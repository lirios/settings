if(NOT TARGET Liri::DBusService)
    find_package(Liri1DBusService REQUIRED)
endif()

# Translations
file(GLOB LiriSettings_TRANSLATIONS "${CMAKE_SOURCE_DIR}/translations/app/*_*.ts")
qt6_add_translation(LiriSettings_QM_FILES ${LiriSettings_TRANSLATIONS})
install(FILES ${LiriSettings_QM_FILES}
	DESTINATION "${KDE_INSTALL_DATADIR}/liri-settings/translations")

set(_sources
    main.cpp
    settingsapp.cpp settingsapp.h
    io.liri.Settings.desktop
    ${LiriSettings_QM_FILES}
)

add_executable(LiriSettings ${_sources})

qt6_add_qml_module(LiriSettings
    URI settings
    QML_FILES
        qml/ErrorPage.qml
        qml/ErrorView.qml
        qml/main.qml
        qml/SettingsPage.qml
        qml/SettingsListItem.qml
)

set_target_properties(LiriSettings PROPERTIES OUTPUT_NAME liri-settings)

target_compile_definitions(LiriSettings PRIVATE -DLIRISETTINGS_VERSION="${PROJECT_VERSION}")

target_link_libraries(LiriSettings
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        Liri::DBusService
)

install(TARGETS LiriSettings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

set(BINDIR "${KDE_INSTALL_FULL_BINDIR}")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/io.liri.Settings.service.in"
               "${CMAKE_CURRENT_BINARY_DIR}/io.liri.Settings.service"
               @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/io.liri.Settings.service"
        DESTINATION "${KDE_INSTALL_DATADIR}/dbus-1/services")
