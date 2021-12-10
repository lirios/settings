liri_add_qml_plugin(SettingsUpdatesQmlPlugin
    MODULE_PATH
        "Liri/Settings/Updates"
    OUTPUT_NAME
        "updatesplugin"
    SOURCES
        plugin.cpp
        rpmdiffmodel.cpp rpmdiffmodel.h
        rpmostree.h
        rpmostreebackend.cpp rpmostreebackend.h
        softwareupdate.cpp softwareupdate.h
        transaction.cpp transaction.h
    QML_FILES
        qmldir
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_FOREACH
    DBUS_INTERFACE_SOURCES
        org.projectatomic.rpmostree1.xml
    DBUS_INTERFACE_FLAGS
        -i rpmostree.h
    LIBRARIES
        Qt::DBus
        Qt::Qml
        Qt::Quick
)

liri_finalize_qml_plugin(SettingsUpdatesQmlPlugin)

liri_add_settings_module(Updates
    CONTENTS
        contents/DetailsPage.qml
        contents/main.qml
        contents/TransactionProgress.qml
        contents/UpdateInProgress.qml
        contents/UpdatesAvailable.qml
)
