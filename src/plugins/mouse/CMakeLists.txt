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

qt5_wrap_ui(FORMS_HEADERS ${FORMS})

add_library(mouse SHARED ${SOURCES} ${FORMS_HEADERS})
set_target_properties(mouse PROPERTIES PREFIX "")
qt5_use_modules(mouse Widgets)
target_link_libraries(mouse HawaiiSystemPreferences)

install(TARGETS mouse LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
