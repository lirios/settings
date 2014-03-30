add_definitions(-DQT_PLUGIN)

set(SOURCES
    backgroundsmodel.cpp
    colorsmodel.cpp
    plugin.cpp
)

set(FILES
    qmldir
)

add_library(backgroundplugin SHARED ${SOURCES})
qt5_use_modules(backgroundplugin Qml Quick)

install(TARGETS backgroundplugin LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/qml/Hawaii/SystemPreferences/Background)
install(FILES ${FILES}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/hawaii/qml/Hawaii/SystemPreferences/Background)
