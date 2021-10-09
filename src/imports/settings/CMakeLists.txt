find_package(Polkit REQUIRED)

if(NOT TARGET Liri::Xdg)
    find_package(Liri1Xdg REQUIRED)
endif()

liri_add_qml_plugin(settings
    MODULE_PATH
        "Liri/Settings"
    SOURCES
        authorizedaction.cpp
        authorizedaction.h
        module.cpp
        module.h
        modulesmodel.cpp
        modulesmodel.h
        plugin.cpp
    QML_FILES
        qml/ModuleContainer.qml
        qml/ModulePage.qml
        qml/ModulePane.qml
        qml/qmldir
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_FOREACH
        QT_NO_KEYWORDS
    LIBRARIES
        Qt5::Core
        Qt5::Gui
        PkgConfig::Polkit
        Liri::Xdg
)

liri_finalize_qml_plugin(settings)
