include_directories(
    ${VibeWidgets_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_definitions(${VibeWidgets_DEFINITIONS} -DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
    backgroundcategoriesmodel.cpp
    backgroundsmodel.cpp
    backgrounditemdelegate.cpp
    wallpaperfinder.cpp
)

set(FORMS
    desktopscreensaverpreflet.ui
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})

add_library(desktop-screensaver SHARED ${SOURCES} ${FORMS_HEADERS})
set_target_properties(desktop-screensaver PROPERTIES PREFIX "")
target_link_libraries(desktop-screensaver ${VibeWidgets_LIBRARIES})

install(TARGETS desktop-screensaver LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
