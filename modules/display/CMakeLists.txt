set(SOURCES
    outputsmodel.cpp
    plugin.cpp
    waylandconfig.cpp
)

set(FILES
    qmldir
)

add_hawaii_preflet(
    VENDOR hawaii
    NAME display
    CONTENTS_DIR contents
    METADATA_TEMPLATE metadata.desktop.in
    SOURCES ${SOURCES}
    QM_FILES_VAR QM_FILES
    DESKTOP_FILE_VAR DESKTOP_FILE
    COMPONENT Runtime
)

add_library(displayplugin SHARED ${SOURCES})
target_link_libraries(displayplugin Qt5::Qml Qt5::Quick GreenIsland::Client)

install(TARGETS displayplugin LIBRARY
        DESTINATION ${QML_INSTALL_DIR}/org/hawaiios/systempreferences/display)
install(FILES ${FILES}
        DESTINATION ${QML_INSTALL_DIR}/org/hawaiios/systempreferences/display)
