add_definitions(-DQT_PLUGIN)

set(SOURCES
    plugin.cpp
    pluginsmodel.cpp
    xdgdesktopfile.cpp
    systemsettingsplugin.cpp
)

add_library(systemsettingsplugin SHARED ${SOURCES})
target_link_libraries(systemsettingsplugin Qt5::Gui Qt5::Qml)

set(FILES
    qmldir
    PrefletPage.qml
)

install(TARGETS systemsettingsplugin LIBRARY
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/SystemSettings)
install(FILES ${FILES}
        DESTINATION ${QML_INSTALL_DIR}/Hawaii/SystemSettings)
