include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${CMAKE_BINARY_DIR}/src/app
)

add_definitions(-DQT_PLUGIN)

configure_file(hawaii-background-panel.desktop.in
               ${CMAKE_CURRENT_BINARY_DIR}/hawaii-background-panel.desktop)

set(SOURCES
    backgroundsmodel.cpp
    preflet.cpp
    plugin.cpp
)

##############################################################################
# Translations
##############################################################################
set(TS_TEMPLATE ${CMAKE_SOURCE_DIR}/translations/plugins/background/template.ts)
file(GLOB QM_SOURCES ${CMAKE_SOURCE_DIR}/translations/plugins/background/*.ts)
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

qt5_add_resources(RESOURCES background.qrc)

add_library(background SHARED ${SOURCES} ${QM_FILES} ${RESOURCES})
set_target_properties(background PROPERTIES PREFIX "")
qt5_use_modules(background Quick)
target_link_libraries(background HawaiiSystemPreferences)

install(TARGETS background LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/plugins/preferences)
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/background/translations)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hawaii-background-panel.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
