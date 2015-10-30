set(FILES
    hawaii-system-preferences.desktop
    hawaii-background-panel.desktop
    hawaii-desktop-panel.desktop
    hawaii-network-panel.desktop
    hawaii-power-panel.desktop
)

install(FILES ${FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
