include_directories(
    ${POLKITQT-1_INCLUDE_DIR}
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

qt5_add_resources(RESOURCES settings.qrc)

add_executable(liri-settings ${SOURCES} ${QM_FILES} ${RESOURCES})
target_link_libraries(liri-settings
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::QuickControls2)
                      
#                      ${POLKITQT-1_GUI_LIBRARY}

install(TARGETS liri-settings
    DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/liri-settings/translations)

vibe_translate_desktop(DESKTOP_FILE
                       SOURCES io.liri.Settings.desktop.in)
install(FILES ${DESKTOP_FILE}
        DESTINATION ${KDE_INSTALL_APPDIR}
        COMPONENT "Runtime")

file(GLOB QML_SOURCES "qml/*.qml")
vibe_translate_ts(QM_FILES
                  SOURCES ${SOURCES} ${QML_SOURCES}
                  TEMPLATE "app"
                  INSTALL_DIR "${DATA_INSTALL_DIR}/liri/settings/translations/app"
                  COMPONENT "Runtime")

add_custom_target(liri-settings_translations ALL DEPENDS ${DESKTOP_FILE} ${QM_FILES})
