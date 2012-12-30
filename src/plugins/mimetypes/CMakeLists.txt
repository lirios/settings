include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
    typesmodel.cpp
)

set(FORMS
    mimetypespreflet.ui
)

set(QM_SOURCES
    translations/it.ts
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})
qt5_add_translation(QM_FILES ${QM_SOURCES})

add_library(mimetypes SHARED ${SOURCES} ${FORMS_HEADERS} ${QM_FILES})
set_target_properties(mimetypes PROPERTIES PREFIX "")
qt5_use_modules(mimetypes Widgets)
target_link_libraries(mimetypes HawaiiSystemPreferences)

install(TARGETS mimetypes LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/mimetypes/translations)
