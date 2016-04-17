set(SOURCES
    backgroundsmodel.cpp
    colorsmodel.cpp
    plugin.cpp
)

set(FILES
    qmldir
)

add_hawaii_preflet(
    VENDOR hawaii
    NAME background
    CONTENTS_DIR contents
    METADATA_TEMPLATE metadata.desktop.in
    SOURCES ${SOURCES}
    QM_FILES_VAR QM_FILES
    DESKTOP_FILE_VAR DESKTOP_FILE
    COMPONENT Runtime
)

add_library(backgroundplugin SHARED ${SOURCES})
target_link_libraries(backgroundplugin Qt5::Qml Qt5::Quick)

install(TARGETS backgroundplugin LIBRARY
        DESTINATION ${QML_INSTALL_DIR}/org/hawaiios/systempreferences/background)
install(FILES ${FILES}
        DESTINATION ${QML_INSTALL_DIR}/org/hawaiios/systempreferences/background)
