include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
)

set(FORMS
    mousepreflet.ui
)

set(QM_SOURCES
    translations/ar.ts
    translations/ast.ts
    translations/bg.ts
    translations/cs_CZ.ts
    translations/de.ts
    translations/el.ts
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

qt5_wrap_ui(FORMS_HEADERS ${FORMS})
qt5_add_translation(QM_FILES ${QM_SOURCES})

add_library(mouse SHARED ${SOURCES} ${FORMS_HEADERS} ${QM_FILES})
set_target_properties(mouse PROPERTIES PREFIX "")
qt5_use_modules(mouse Widgets)
target_link_libraries(mouse HawaiiSettings)

install(TARGETS mouse LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-settings/plugins/mouse/translations)
