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

qt5_wrap_ui(FORMS_HEADERS ${FORMS})

add_library(mimetypes SHARED ${SOURCES} ${FORMS_HEADERS})
set_target_properties(mimetypes PROPERTIES PREFIX "")
qt5_use_modules(mimetypes Widgets)
target_link_libraries(mimetypes HawaiiSystemPreferences)

install(TARGETS mimetypes LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
