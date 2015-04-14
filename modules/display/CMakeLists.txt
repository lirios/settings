# Find KScreen
find_package(KF5Screen 5.2 REQUIRED)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    outputsmodel.cpp
    plugin.cpp
)

set(FILES
    qmldir
)

add_library(displayplugin SHARED ${SOURCES})
target_link_libraries(displayplugin Qt5::Qml Qt5::Quick KF5::Screen)

install(TARGETS displayplugin LIBRARY
    DESTINATION ${QML_INSTALL_DIR}/org/hawaii/systempreferences/display)
install(FILES ${FILES}
    DESTINATION ${QML_INSTALL_DIR}/org/hawaii/systempreferences/display)

hawaii_install_module(org.hawaii.systempreferences.display contents hawaii)
