include_directories(
    ${KCoreAddons_INCLUDE_DIRS}
    ${KConfig_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/3rdparty/libqtxdg
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${CMAKE_BINARY_DIR}/src/app
)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/3rdparty/libqtxdg/xdgdesktopfile.cpp
    preflet.cpp
    plugin.cpp
    abstractitem.cpp
    backgrounditem.cpp
    wallpaperitem.cpp
    wallpapersmodel.cpp
    backgroundsettings.cpp
)

set(QM_SOURCES
  translations/af.ts
  translations/ar.ts
  translations/de.ts
  translations/el.ts
  translations/es_AR.ts
  translations/es.ts
  translations/fr.ts
  translations/hu.ts
  translations/id.ts
  translations/it.ts
  translations/ja_JP.ts
  translations/kk.ts
  translations/nl.ts
  translations/no.ts
  translations/pl.ts
  translations/pt_BR.ts
  translations/pt.ts
  translations/ru.ts
  translations/si_LK.ts
  translations/sk.ts
  translations/tr.ts
  translations/vi.ts
  translations/zh_CN.ts
)

qt5_add_translation(QM_FILES ${QM_SOURCES})
qt5_add_resources(RESOURCES background.qrc)

add_library(background SHARED ${SOURCES} ${QM_FILES} ${RESOURCES})
set_target_properties(background PROPERTIES PREFIX "")
qt5_use_modules(background Quick Configuration Xdg)
target_link_libraries(background HawaiiSystemPreferences)

install(TARGETS background LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/plugins/preferences)
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/background/translations)
