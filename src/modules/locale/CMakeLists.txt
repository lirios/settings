ecm_add_qml_module(SettingsLocaleQmlPlugin
    URI Liri.Settings.Locale
    VERSION 1.0
    CLASS_NAME LocaleSettingsPlugin
    NO_GENERATE_PLUGIN_SOURCE
)

target_sources(SettingsLocaleQmlPlugin
    PRIVATE
        localefiltermodel.cpp localefiltermodel.h
        localemanager.cpp localemanager.h
        localemodel.cpp localemodel.h
        plugin.cpp
        systemlocale.cpp systemlocale.h
)

target_link_libraries(SettingsLocaleQmlPlugin
    PRIVATE
        Qt6::Concurrent
        Qt6::DBus
        Qt6::Qml
        Qt6::Quick
)

ecm_finalize_qml_module(SettingsLocaleQmlPlugin)

liri_add_settings_module(Locale
    CONTENTS
        contents/main.qml
        contents/FormatsDialog.qml
        contents/LanguageDialog.qml
        contents/RadioIndicator.qml
        contents/RegionDelegate.qml
)
