include_directories(
    ${QtConfiguration_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
)

configure_file(hawaii-keyboard-panel.desktop.in
               ${CMAKE_CURRENT_BINARY_DIR}/hawaii-keyboard-panel.desktop)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
    keyboardsettings.cpp
)

set(QM_SOURCES
  translations/it.ts
)

qt5_add_resources(RESOURCES keyboard.qrc)
qt5_add_translation(QM_FILES ${QM_SOURCES})

add_library(keyboard SHARED ${SOURCES} ${QM_FILES} ${RESOURCES})
set_target_properties(keyboard PROPERTIES PREFIX "")
qt5_use_modules(keyboard Quick)
target_link_libraries(keyboard
    HawaiiSystemPreferences
    ${QtConfiguration_LIBRARIES}
)

install(TARGETS keyboard LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/plugins/preferences)
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/keyboard/translations)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hawaii-keyboard-panel.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
