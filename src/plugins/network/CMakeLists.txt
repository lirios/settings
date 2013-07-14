include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    networkpreflet.cpp
    networkplugin.cpp
)

set(QM_SOURCES
    translations/it.ts
)

qt5_add_translation(QM_FILES ${QM_SOURCES})
qt5_add_resources(RESOURCES network.qrc)

#add_library(network SHARED ${SOURCES} ${QM_FILES} ${RESOURCES})
add_library(network SHARED ${SOURCES} ${RESOURCES})
set_target_properties(network PROPERTIES PREFIX "")
qt5_use_modules(network Quick)
target_link_libraries(network HawaiiSystemPreferences)

install(TARGETS network LIBRARY
    DESTINATION ${QT_PLUGINS_DIR}/hawaii/preferences)
#install(FILES ${QM_FILES}
#    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/network/translations)
