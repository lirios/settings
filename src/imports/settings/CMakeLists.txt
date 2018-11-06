find_package(Qt5Xdg REQUIRED)
find_package(Polkit REQUIRED)

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
        Qt5::Xml
        Qt5::Gui
        Qt5Xdg
        PkgConfig::Polkit
)
