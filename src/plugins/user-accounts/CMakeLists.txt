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
    preflet.ui
)

set(RESOURCES
    resources.qrc
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})

add_library(user-accounts SHARED ${SOURCES} ${FORMS_HEADERS})
set_target_properties(user-accounts PROPERTIES PREFIX "")
qt5_use_modules(user-accounts Widgets)
target_link_libraries(user-accounts HawaiiSystemPreferences)

install(TARGETS user-accounts LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
