ecm_add_qml_module(SettingsBackgroundQmlPlugin
    URI Liri.Settings.Background
    VERSION 1.0
    CLASS_NAME BackgroundCorePlugin
    NO_GENERATE_PLUGIN_SOURCE
)

target_sources(SettingsBackgroundQmlPlugin
    PRIVATE
        backgroundsmodel.cpp backgroundsmodel.h
        colorsmodel.cpp colorsmodel.h
        plugin.cpp
)

target_link_libraries(SettingsBackgroundQmlPlugin
    PRIVATE
        Qt6::Qml
        Qt6::Quick
)

ecm_finalize_qml_module(SettingsBackgroundQmlPlugin)

liri_add_settings_module(Background
    CONTENTS
        contents/ColorButton.qml
        contents/GradientPage.qml
        contents/main.qml
        contents/SelectorPage.qml
        contents/Selector.qml
        contents/SolidPage.qml
        contents/WallpaperPage.qml
)
