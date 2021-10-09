liri_add_qml_plugin(display
    MODULE_PATH
        "Liri/Settings/Display"
    SOURCES
        outputdevice.h
        outputsmodel.cpp
        outputsmodel.h
        plugin.cpp
    QML_FILES
        qmldir
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_FOREACH
    DBUS_INTERFACE_SOURCES
        data/io.liri.Shell.OutputConfiguration1.xml
        data/io.liri.Shell.OutputDevice1.xml
        data/io.liri.Shell.OutputManagement1.xml
    DBUS_INTERFACE_FLAGS
        -i outputdevice.h
    LIBRARIES
        Qt5::DBus
        Qt5::Qml
        Qt5::Quick
)

liri_finalize_qml_plugin(display)

liri_add_settings_module(Display
    CONTENTS
        contents/DetailsDialog.qml
        contents/main.qml
        contents/OutputPreview.qml
)
