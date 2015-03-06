add_definitions(-DQT_PLUGIN)

set(SOURCES
    keyboarddata.cpp
    keyboardmodel.cpp
    keyboardlayout.cpp
    keyboardlayoutvariant.cpp
    plugin.cpp
)

set(FILES
    qmldir
)

add_library(keyboardplugin SHARED ${SOURCES})
target_link_libraries(keyboardplugin Qt5::Qml Qt5::Quick)

install(TARGETS keyboardplugin LIBRARY
    DESTINATION ${QML_INSTALL_DIR}/org/hawaii/systempreferences/keyboard)
install(FILES ${FILES}
    DESTINATION ${QML_INSTALL_DIR}/org/hawaii/systempreferences/keyboard)

hawaii_install_module(org.hawaii.systempreferences.keyboard contents hawaii)
