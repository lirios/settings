include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${VibeCore_INCLUDE_DIRS}
)

add_definitions(-DQT_PLUGIN)

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
qt5_use_modules(desktop Widgets)
target_link_libraries(desktop
    ${VibeCore_LIBRARIES}
    HawaiiSystemPreferences
)

install(TARGETS desktop LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
