include_directories(
    ${VibeWidgets_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_definitions(${VibeWidgets_DEFINITIONS} -DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
)

set(HEADERS
    preflet.h
    plugin.h
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
target_link_libraries(user-accounts ${VibeWidgets_LIBRARIES})

install(TARGETS user-accounts LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
