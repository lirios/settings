find_package(Libcrypt REQUIRED)

liri_add_qml_plugin(SettingsUsersQmlPlugin
    MODULE_PATH
        "Liri/Settings/Users"
    OUTPUT_NAME
        "usersplugin"
    SOURCES
        password.cpp
        password.h
        plugin.cpp
    QML_FILES
        qmldir
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_FOREACH
    LIBRARIES
        Qt5::Qml
        Qt5::Quick
        Libcrypt::Libcrypt
)

liri_finalize_qml_plugin(SettingsUsersQmlPlugin)

liri_add_settings_module(Users
    CONTENTS
        contents/main.qml
        contents/PhotoPicker.qml
        contents/UserAddDialog.qml
        contents/UserListItem.qml
        contents/UserPage.qml
)
