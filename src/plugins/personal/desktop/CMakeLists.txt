include_directories(
    ${VibeWidgets_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_definitions(${VibeWidgets_DEFINITIONS} -DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
    backgrounditem.cpp
    wallpaperitem.cpp
#    coloritem.cpp
    wallpapermodel.cpp
    wallpaperfinder.cpp
    wallpapersizefinder.cpp
    backgrounditemdelegate.cpp
)

set(FORMS
    desktoppreflet.ui
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})

add_library(desktop SHARED ${SOURCES} ${FORMS_HEADERS})
set_target_properties(desktop PROPERTIES PREFIX "")
target_link_libraries(desktop ${VibeWidgets_LIBRARIES})

install(TARGETS desktop LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
