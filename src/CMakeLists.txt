include_directories(
    ${VibeWidgets_INCLUDE_DIRS}
)

add_definitions(${VibeWidgets_DEFINITIONS})

set(SOURCES
    main.cpp
    mainwindow.cpp
    categoriesmodel.cpp
)

set(HEADERS
    mainwindow.h
    categoriesmodel.h
)

set(UI_FILES
    mainwindow.ui
)

qt5_wrap_ui(FORM_HEADERS ${UI_FILES})

add_executable(system-preferences ${SOURCES} ${FORM_HEADERS})
target_link_libraries(system-preferences ${VibeWidgets_LIBRARIES})

configure_file(system-preferences.desktop.in system-preferences.desktop)

install(FILES system-preferences.desktop DESTINATION ${CMAKE_INSTALL_APPSDIR})
set_target_properties(system-preferences PROPERTIES COMPILE_FLAGS ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS})
install(TARGETS system-preferences DESTINATION ${CMAKE_INSTALL_PROGSDIR})

add_subdirectory(personal)
add_subdirectory(hardware)
add_subdirectory(system)
