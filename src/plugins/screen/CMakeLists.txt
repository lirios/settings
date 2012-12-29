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
    screenpreflet.ui
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})

add_library(screen SHARED ${SOURCES} ${FORMS_HEADERS})
set_target_properties(screen PROPERTIES PREFIX "")
qt5_use_modules(screen Widgets)
target_link_libraries(screen HawaiiSystemPreferences)

install(TARGETS screen LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
