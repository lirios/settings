include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_BINARY_DIR}/src/lib
    ${VibeCore_INCLUDE_DIRS}
)

add_definitions(-DQT_PLUGIN)

set(SOURCES
    preflet.cpp
    useritemdelegate.cpp
    plugin.cpp
    changepassworddialog.cpp
)

set(FORMS
    userspreflet.ui
    changepassworddialog.ui
)

set(QM_SOURCES
    translations/it.ts
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})
qt5_add_translation(QM_FILES ${QM_SOURCES})

add_library(user-accounts SHARED ${SOURCES} ${FORMS_HEADERS} ${QM_FILES})
set_target_properties(user-accounts PROPERTIES PREFIX "")
qt5_use_modules(user-accounts Widgets AccountsService)
target_link_libraries(user-accounts
    ${VibeCore_LIBRARIES}
    HawaiiSystemPreferences
)

install(TARGETS user-accounts LIBRARY
    DESTINATION ${CMAKE_INSTALL_PLUGINSDIR}/preferences)
install(FILES ${QM_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/hawaii-system-preferences/plugins/user-accounts/translations)
