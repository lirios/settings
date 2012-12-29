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

qt5_wrap_ui(FORMS_HEADERS ${FORMS})

add_library(sound SHARED ${SOURCES} ${FORMS_HEADERS})
set_target_properties(sound PROPERTIES PREFIX "")
qt5_use_modules(sound Widgets)
target_link_libraries(sound
    ${VibeWidgets_LIBRARIES}
    HawaiiSystemPreferences
)

install(TARGETS sound LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
