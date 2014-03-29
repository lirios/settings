include_directories(
    ${HF1HawaiiShell_INCLUDE_DIRS}
    ${HawaiiShell_INCLUDE_DIRS}
    ${POLKITQT-1_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${CMAKE_SOURCE_DIR}/src/lib
)

# Create the cmakedirs.h header file
configure_file(cmakedirs.h.in ${CMAKE_CURRENT_BINARY_DIR}/cmakedirs.h)

# Create the config.h header file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY
)

set(SOURCES
    main.cpp
    prefletsmodel.cpp
    prefletsproxymodel.cpp
    plugin.cpp
    pluginmanager.cpp
)

##############################################################################
# Translations
##############################################################################
set(TS_TEMPLATE ${CMAKE_SOURCE_DIR}/translations/app/template.ts)
file(GLOB QM_SOURCES ${CMAKE_SOURCE_DIR}/translations/app/*.ts)
list(REMOVE_ITEM QM_SOURCES ${TS_TEMPLATE})

if(REFRESH_TRANSLATIONS)
    file(GLOB_RECURSE TS_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
    file(GLOB_RECURSE TS_QML_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qml)
    set(TS_SOURCES ${TS_CPP_FILES} ${TS_QML_FILES})

    qt5_create_translation(QM_FILES ${TS_SOURCES} ${QM_SOURCES})
else()
    qt5_add_translation(QM_FILES ${QM_SOURCES})
endif()
##############################################################################

qt5_add_resources(RESOURCES system-preferences.qrc)

add_executable(hawaii-system-preferences ${SOURCES} ${QM_FILES} ${RESOURCES})
qt5_use_modules(hawaii-system-preferences Qml Quick Widgets)
set_target_properties(hawaii-system-preferences PROPERTIES
    LINK_FLAGS "-L${POLKITQT-1_LIB_DIR}"
)
target_link_libraries(hawaii-system-preferences
    HF1::HawaiiShell
    ${POLKITQT-1_GUI_LIBRARY}
    HawaiiSystemPreferences
)

install(TARGETS hawaii-system-preferences
    DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/translations)
