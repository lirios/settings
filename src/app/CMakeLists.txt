include_directories(
    ${VibeWidgets_INCLUDE_DIRS}
)

add_definitions(${VibeWidgets_DEFINITIONS})

# Create the cmakedirs.h header file
configure_file(cmakedirs.h.in ${CMAKE_CURRENT_BINARY_DIR}/cmakedirs.h)

set(SOURCES
    main.cpp
    mainwindow.cpp
    categorydrawer.cpp
    menuitem.cpp
    menumodel.cpp
    menuproxymodel.cpp
)

add_executable(system-preferences ${SOURCES})
target_link_libraries(system-preferences ${VibeWidgets_LIBRARIES})

configure_file(system-preferences.desktop.in system-preferences.desktop)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/system-preferences.desktop DESTINATION ${CMAKE_INSTALL_APPLICATIONSDIR})
set_target_properties(system-preferences PROPERTIES COMPILE_FLAGS ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS})
install(TARGETS system-preferences DESTINATION ${CMAKE_INSTALL_BINDIR})
