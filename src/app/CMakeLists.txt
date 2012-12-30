include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
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

set(QM_SOURCES
    translations/it.ts
)

qt5_add_translation(QM_FILES ${QM_SOURCES})

add_executable(hawaii-system-preferences ${SOURCES} ${QM_FILES})
qt5_use_modules(hawaii-system-preferences Widgets)
target_link_libraries(hawaii-system-preferences
    ${VibeWidgets_LIBRARIES}
    HawaiiSystemPreferences
)

configure_file(hawaii-system-preferences.desktop.in hawaii-system-preferences.desktop)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hawaii-system-preferences.desktop
    DESTINATION ${CMAKE_INSTALL_APPLICATIONSDIR})
install(TARGETS hawaii-system-preferences
    DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/translations)
