include_directories(
    ${CMAKE_SOURCE_DIR}/3rdparty/libqtxdg
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${CMAKE_SOURCE_DIR}/src/lib
    ${POLKITQT-1_INCLUDE_DIR}
)

# Create the cmakedirs.h header file
configure_file(cmakedirs.h.in ${CMAKE_CURRENT_BINARY_DIR}/cmakedirs.h)

# Create the config.h header file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY
)

set(SOURCES
    main.cpp
    prefletsmodel.cpp
    prefletsproxymodel.cpp
    plugin.cpp
    pluginmanager.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/libqtxdg/xdgdesktopfile.cpp
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

qt5_add_translation(QM_FILES ${QM_SOURCES})
qt5_add_resources(RESOURCES system-preferences.qrc)

add_executable(hawaii-system-preferences ${SOURCES} ${QM_FILES} ${RESOURCES})
qt5_use_modules(hawaii-system-preferences Qml Quick Widgets)
set_target_properties(hawaii-system-preferences PROPERTIES
    LINK_FLAGS "-L${POLKITQT-1_LIB_DIR}"
)
target_link_libraries(hawaii-system-preferences
    ${POLKITQT-1_GUI_LIBRARY}
    HawaiiSystemPreferences
)

install(TARGETS hawaii-system-preferences
    DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/translations)
