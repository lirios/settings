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

add_hawaii_preflet(
    VENDOR hawaii
    DOMAIN org.hawaiios.systempreferences
    NAME keyboard
    CONTENTS_DIR contents
    METADATA_TEMPLATE metadata.desktop.in
    SOURCES ${SOURCES}
    QM_FILES_VAR QM_FILES
    DESKTOP_FILE_VAR DESKTOP_FILE
    COMPONENT Runtime
)

add_library(keyboardplugin SHARED ${SOURCES})
target_link_libraries(keyboardplugin Qt5::Qml Qt5::Quick)

install(TARGETS keyboardplugin LIBRARY
    DESTINATION ${QML_INSTALL_DIR}/org/hawaiios/systempreferences/keyboard)
install(FILES ${FILES}
    DESTINATION ${QML_INSTALL_DIR}/org/hawaiios/systempreferences/keyboard)
