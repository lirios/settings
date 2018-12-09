# Translations
file(GLOB LiriSettings_TRANSLATIONS "${CMAKE_CURRENT_SOURCE_DIR}/translations/*_*.ts")
qt5_add_translation(LiriSettings_QM_FILES ${LiriSettings_TRANSLATIONS})
install(FILES ${LiriSettings_QM_FILES}
        DESTINATION "${INSTALL_DATADIR}/liri-settings/translations")

liri_translate_desktop(_desktop_file SOURCES "io.liri.Settings.desktop.in")

liri_add_executable(LiriSettings
    OUTPUT_NAME
        "liri-settings"
    SOURCES
        main.cpp
        ${LiriSettings_QM_FILES}
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_FOREACH
        LIRISETTINGS_VERSION="${PROJECT_VERSION}"
    DESKTOP
        "${_desktop_file}"
    RESOURCES
        settings.qrc
    LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Qml
        Qt5::Quick
        Qt5::QuickControls2
)
