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

set(QM_SOURCES
    translations/it.ts
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})
qt5_add_translation(QM_FILES ${QM_SOURCES})

add_library(desktop SHARED ${SOURCES} ${FORMS_HEADERS} ${QM_FILES})
set_target_properties(desktop PROPERTIES PREFIX "")
qt5_use_modules(desktop Widgets)
target_link_libraries(desktop
    ${VibeCore_LIBRARIES}
    HawaiiSystemPreferences
)

install(TARGETS desktop LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/desktop/translations)
