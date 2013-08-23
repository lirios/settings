include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${VibeCore_INCLUDE_DIRS}
)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
    launchersettings.cpp
)

set(QM_SOURCES
    translations/it.ts
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})
qt5_add_resources(RESOURCES desktop.qrc)
#qt5_add_translation(QM_FILES ${QM_SOURCES})

#add_library(desktop SHARED ${SOURCES} ${QM_FILES} ${RESOURCES})
add_library(desktop SHARED ${SOURCES} ${QM_FILES} ${RESOURCES})
set_target_properties(desktop PROPERTIES PREFIX "")
qt5_use_modules(desktop Quick Configuration)
target_link_libraries(desktop HawaiiSystemPreferences)

install(TARGETS desktop LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/plugins/preferences)
#install(FILES ${QM_FILES}
#    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/desktop/translations)
