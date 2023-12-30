find_package(Libcrypt REQUIRED)

ecm_add_qml_module(SettingsUsersQmlPlugin
    URI Liri.Settings.Users
    VERSION 1.0
    CLASS_NAME UsersPlugin
    NO_GENERATE_PLUGIN_SOURCE
)

target_sources(SettingsUsersQmlPlugin
    PRIVATE
        password.cpp password.h
        plugin.cpp
)

target_link_libraries(SettingsUsersQmlPlugin
    PRIVATE
        Qt6::Qml
        Qt6::Quick
        Libcrypt::Libcrypt
)

ecm_finalize_qml_module(SettingsUsersQmlPlugin)

liri_add_settings_module(Users
    CONTENTS
        contents/main.qml
        contents/PhotoPicker.qml
        contents/UserAddDialog.qml
        contents/UserListItem.qml
        contents/UserPage.qml
)
