set(FILES
    liri-background-panel.desktop
    liri-desktop-panel.desktop
    liri-network-panel.desktop
    liri-power-panel.desktop
)

install(FILES ${FILES}
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
