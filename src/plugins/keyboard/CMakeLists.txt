include_directories(
    ${QtConfiguration_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
)

configure_file(hawaii-keyboard-panel.desktop.in
               ${CMAKE_CURRENT_BINARY_DIR}/hawaii-keyboard-panel.desktop)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
    keyboardsettings.cpp
)

set(QM_SOURCES
    translations/af.ts
    translations/ar.ts
    translations/ast.ts
    translations/bg.ts
    translations/cs_CZ.ts
    translations/de.ts
    translations/el.ts
    translations/es_AR.ts
    translations/es.ts
    translations/fa_IR.ts
    translations/fr.ts
    translations/hu.ts
    translations/id.ts
    translations/it_IT.ts
    translations/it.ts
    translations/ja_JP.ts
    translations/kk.ts
    translations/nl_NL.ts
    translations/nl.ts
    translations/no.ts
    translations/pl.ts
    translations/pt_BR.ts
    translations/pt.ts
    translations/ru.ts
    translations/si_LK.ts
    translations/sk.ts
    translations/template.ts
    translations/tr.ts
    translations/vi.ts
    translations/zh_CN.ts
)

qt5_add_resources(RESOURCES keyboard.qrc)
qt5_add_translation(QM_FILES ${QM_SOURCES})

add_library(keyboard SHARED ${SOURCES} ${QM_FILES} ${RESOURCES})
set_target_properties(keyboard PROPERTIES PREFIX "")
qt5_use_modules(keyboard Quick)
target_link_libraries(keyboard
    HawaiiSystemPreferences
    ${QtConfiguration_LIBRARIES}
)

install(TARGETS keyboard LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/plugins/preferences)
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/keyboard/translations)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hawaii-keyboard-panel.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
