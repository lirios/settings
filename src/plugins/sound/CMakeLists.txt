include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${VibeWidgets_INCLUDE_DIRS}
)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    plugin.cpp
    soundcardmodel.cpp
)

set(HEADERS
    preflet.h
    plugin.h
    soundcardmodel.h
)

set(FORMS
    preflet.ui
)

set(QM_SOURCES
    translations/it.ts
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})
qt5_add_translation(QM_FILES ${QM_SOURCES})

add_library(sound SHARED ${SOURCES} ${FORMS_HEADERS} ${QM_FILES})
set_target_properties(sound PROPERTIES PREFIX "")
qt5_use_modules(sound Widgets)
target_link_libraries(sound
    ${VibeWidgets_LIBRARIES}
    HawaiiSystemPreferences
)

install(TARGETS sound LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/sound/user-accounts/translations)
