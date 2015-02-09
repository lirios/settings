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
target_link_libraries(backgroundplugin Qt5::Qml Qt5::Quick)

install(TARGETS backgroundplugin LIBRARY
    DESTINATION ${QML_INSTALL_DIR}/org/hawaii/systempreferences/background)
install(FILES ${FILES}
    DESTINATION ${QML_INSTALL_DIR}/org/hawaii/systempreferences/background)

hawaii_install_module(org.hawaii.systempreferences.background contents hawaii)
