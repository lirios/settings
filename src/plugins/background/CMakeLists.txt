include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${VibeCore_INCLUDE_DIRS}
)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
)

set(QM_SOURCES
    translations/it.ts
)

qt5_add_translation(QM_FILES ${QM_SOURCES})
qt5_add_resources(RESOURCES background.qrc)

#add_library(background SHARED ${SOURCES} ${QM_FILES} ${RESOURCES})
add_library(background SHARED ${SOURCES} ${RESOURCES})
set_target_properties(background PROPERTIES PREFIX "")
qt5_use_modules(background Quick)
target_link_libraries(background HawaiiSystemPreferences)

install(TARGETS background LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
#install(FILES ${QM_FILES}
#    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/background/translations)
