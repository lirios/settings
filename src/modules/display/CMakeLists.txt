ecm_add_qml_module(DisplayQmlPlugin
    URI Liri.Settings.Display
    VERSION 1.0
    CLASS_NAME DisplayPlugin
    NO_GENERATE_PLUGIN_SOURCE
)

set_source_files_properties(
    data/io.liri.Shell.OutputDevice1.xml
    PROPERTIES INCLUDE outputdevice.h
)

qt6_add_dbus_interfaces(
    _dbus_sources
    data/io.liri.Shell.OutputConfiguration1.xml
    data/io.liri.Shell.OutputDevice1.xml
    data/io.liri.Shell.OutputManagement1.xml
)

target_sources(DisplayQmlPlugin
    PRIVATE
        outputdevice.h
        outputsmodel.cpp outputsmodel.h
        plugin.cpp
        ${_dbus_sources}
)

target_link_libraries(DisplayQmlPlugin
    PRIVATE
        Qt6::DBus
        Qt6::Qml
        Qt6::Quick
)

ecm_finalize_qml_module(DisplayQmlPlugin)

liri_add_settings_module(Display
    CONTENTS
        contents/DetailsDialog.qml
        contents/main.qml
        contents/OutputPreview.qml
)
