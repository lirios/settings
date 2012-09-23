include_directories(
    ${VibeWidgets_INCLUDE_DIRS}
)

add_definitions(${VibeWidgets_DEFINITIONS} -DQT_PLUGIN)

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
target_link_libraries(sound ${VibeWidgets_LIBRARIES})

install(TARGETS sound LIBRARY DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
