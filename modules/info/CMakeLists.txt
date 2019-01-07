file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/version.js" "var version = \"${PROJECT_VERSION}\";")

liri_add_settings_module(Info
    CONTENTS
        contents/logo.png
        contents/main.qml
        "${CMAKE_CURRENT_BINARY_DIR}/version.js"
)
