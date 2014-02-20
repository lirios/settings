include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
)

configure_file(hawaii-network-panel.desktop.in
               ${CMAKE_CURRENT_BINARY_DIR}/hawaii-network-panel.desktop)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    networkpreflet.cpp
    networkplugin.cpp
)

##############################################################################
# Translations
##############################################################################
set(TS_TEMPLATE ${CMAKE_SOURCE_DIR}/translations/plugins/network/template.ts)
file(GLOB QM_SOURCES ${CMAKE_SOURCE_DIR}/translations/plugins/network/*.ts)
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

qt5_add_resources(RESOURCES network.qrc)

add_library(network SHARED ${SOURCES} ${QM_SOURCES} ${RESOURCES})
set_target_properties(network PROPERTIES PREFIX "")
qt5_use_modules(network Quick)
target_link_libraries(network HawaiiSystemPreferences)

install(TARGETS network LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/plugins/preferences)
#install(FILES ${QM_FILES}
#    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/network/translations)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hawaii-network-panel.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
