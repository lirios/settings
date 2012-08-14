include_directories(
    ${VibeWidgets_INCLUDE_DIRS}
)

add_definitions(${VibeWidgets_DEFINITIONS})

set(SOURCES
    main.cpp
    mainwindow.cpp
    categorydrawer.cpp
    categorizedview.cpp
    menuitem.cpp
    menumodel.cpp
    menuproxymodel.cpp
)

add_executable(system-preferences ${SOURCES})
target_link_libraries(system-preferences ${VibeWidgets_LIBRARIES})

configure_file(system-preferences.desktop.in system-preferences.desktop)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/system-preferences.desktop DESTINATION ${CMAKE_INSTALL_APPSDIR})
set_target_properties(system-preferences PROPERTIES COMPILE_FLAGS ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS})
install(TARGETS system-preferences DESTINATION ${CMAKE_INSTALL_PROGSDIR})
