ecm_add_qml_module(SettingsKeyboardQmlPlugin
    URI Liri.Settings.Keyboard
    VERSION 1.0
    CLASS_NAME KeyboardPlugin
    NO_GENERATE_PLUGIN_SOURCE
)

target_sources(SettingsKeyboardQmlPlugin
    PRIVATE
        keyboarddata.cpp keyboarddata.h
        keyboardlayout.cpp keyboardlayout.h
        keyboardlayoutvariant.cpp keyboardlayoutvariant.h
        keyboardmodel.cpp keyboardmodel.h
        keybordlayoutsmodel.cpp keybordlayoutsmodel.h
        plugin.cpp
)

target_link_libraries(SettingsKeyboardQmlPlugin
    PRIVATE
        Qt6::Qml
        Qt6::Quick
)

ecm_finalize_qml_module(SettingsKeyboardQmlPlugin)

liri_add_settings_module(Keyboard
    CONTENTS
        contents/AddDialog.qml
        contents/LayoutPage.qml
        contents/main.qml
        contents/TypingPage.qml
)
