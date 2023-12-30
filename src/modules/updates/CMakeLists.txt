set_source_files_properties(
    org.projectatomic.rpmostree1.xml
    PROPERTIES INCLUDE rpmostreedbus.h
)
qt6_add_dbus_interface(_dbus_sources org.projectatomic.rpmostree1.xml rpmostree1_interface)

ecm_add_qml_module(SettingsUpdatesQmlPlugin
    URI Liri.Settings.Updates
    VERSION 1.0
    CLASS_NAME UpdatesPlugin
    NO_GENERATE_PLUGIN_SOURCE
)

target_sources(SettingsUpdatesQmlPlugin
    PRIVATE
        plugin.cpp
        rpmdiffmodel.cpp rpmdiffmodel.h
        rpmostreedbus.h
        rpmostreebackend.cpp rpmostreebackend.h
        softwareupdate.cpp softwareupdate.h
        transaction.cpp transaction.h
        ${_dbus_sources}
)

target_link_libraries(SettingsUpdatesQmlPlugin
    PRIVATE
        Qt6::DBus
        Qt6::Qml
        Qt6::Quick
)

ecm_finalize_qml_module(SettingsUpdatesQmlPlugin)

liri_add_settings_module(Updates
    CONTENTS
        contents/DetailsPage.qml
        contents/main.qml
        contents/TransactionProgress.qml
        contents/UpdateInProgress.qml
        contents/UpdatesAvailable.qml
)
