include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${POLKITQT-1_INCLUDE_DIR}
)

# Create the cmakedirs.h header file
configure_file(cmakedirs.h.in ${CMAKE_CURRENT_BINARY_DIR}/cmakedirs.h)

set(SOURCES
    main.cpp
    categoriesmodel.cpp
    prefletsmodel.cpp
    prefletsproxymodel.cpp
)

set(QM_SOURCES
    translations/it.ts
)

qt5_add_translation(QM_FILES ${QM_SOURCES})

qt5_add_resources(RESOURCES system-preferences.qrc)

add_executable(hawaii-system-preferences ${SOURCES} ${QM_FILES} ${RESOURCES})
qt5_use_modules(hawaii-system-preferences Qml Quick Widgets)
set_target_properties(hawaii-system-preferences PROPERTIES
    LINK_FLAGS "-L${POLKITQT-1_LIB_DIR}"
)
target_link_libraries(hawaii-system-preferences
    ${POLKITQT-1_GUI_LIBRARY}
    HawaiiSystemPreferences
)

install(TARGETS hawaii-system-preferences
    DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/translations)
