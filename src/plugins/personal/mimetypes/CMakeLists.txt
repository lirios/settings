include_directories(
    ${VibeWidgets_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_definitions(${VibeWidgets_DEFINITIONS} -DQT_PLUGIN)

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
target_link_libraries(mimetypes ${VibeWidgets_LIBRARIES})

install(TARGETS mimetypes LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
