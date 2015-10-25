set(SOURCES
    outputsmodel.cpp
    plugin.cpp
)

set(FILES
    qmldir
)

add_library(displayplugin MODULE ${SOURCES})
target_link_libraries(displayplugin Qt5::Qml Qt5::Quick KF5::Screen)

install(TARGETS displayplugin LIBRARY
    DESTINATION ${QML_INSTALL_DIR}/org/hawaiios/systempreferences/display)
install(FILES ${FILES}
    DESTINATION ${QML_INSTALL_DIR}/org/hawaiios/systempreferences/display)

hawaii_install_module(org.hawaiios.systempreferences.display contents hawaii)
