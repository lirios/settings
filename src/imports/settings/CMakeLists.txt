find_package(Polkit REQUIRED)

if(NOT TARGET Liri::Xdg)
    find_package(Liri1Xdg REQUIRED)
endif()

ecm_add_qml_module(SettingsQmlPlugin
    URI Liri.Settings
    VERSION 1.0
    CLASS_NAME SettingsPlugin
    NO_GENERATE_PLUGIN_SOURCE
)

target_compile_definitions(SettingsQmlPlugin
    PRIVATE
        -DQT_NO_KEYWORDS
)

target_sources(SettingsQmlPlugin
    PRIVATE
        authorizedaction.cpp authorizedaction.h
        module.cpp module.h
        modulesmodel.cpp modulesmodel.h
        plugin.cpp
)

ecm_target_qml_sources(SettingsQmlPlugin
    SOURCES
        qml/ModuleContainer.qml
        qml/ModulePage.qml
        qml/ModulePane.qml
)

target_link_libraries(SettingsQmlPlugin
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        PkgConfig::Polkit
        Liri::Xdg
)

ecm_finalize_qml_module(SettingsQmlPlugin)
