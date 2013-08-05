include_directories(
    ${KCoreAddons_INCLUDE_DIRS}
    ${KConfig_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
    abstractitem.cpp
    backgrounditem.cpp
    wallpaperitem.cpp
    wallpapersmodel.cpp
    backgroundsettings.cpp
)

set(QM_SOURCES
    translations/it.ts
)

qt5_add_translation(QM_FILES ${QM_SOURCES})
qt5_add_resources(RESOURCES background.qrc)

set(KCFG_FILES
    ${CMAKE_BINARY_DIR}/data/settings/hawaiisettings.kcfgc
)
kconfig_add_kcfg_files(SOURCES ${KCFG_FILES})

#add_library(background SHARED ${SOURCES} ${QM_FILES} ${RESOURCES})
add_library(background SHARED ${SOURCES} ${RESOURCES})
set_target_properties(background PROPERTIES PREFIX "")
qt5_use_modules(background Quick Xdg)
target_link_libraries(background
    HawaiiSystemPreferences
    ${KConfig_LIBRARIES}
)

install(TARGETS background LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/plugins/preferences)
#install(FILES ${QM_FILES}
#    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/background/translations)
