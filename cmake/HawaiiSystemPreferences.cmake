#
# hawaii_install_module(module srcpath dstpath)
#
# Installs a Hawaii System Preferences module.
#
# \param module the module name (something like org.vendor.systempreferences.module)
# \param srcpath the source path to install from
# \param dstpath the vendor-specific destination subdirectory
#
macro(hawaii_install_module module srcpath dstpath)
    install(DIRECTORY ${srcpath}/
            DESTINATION ${DATA_INSTALL_DIR}/hawaii-system-preferences/modules/${dstpath}/${module}
            PATTERN .svn EXCLUDE
            PATTERN CMakeLists.txt EXCLUDE
            PATTERN Messages.sh EXCLUDE
            PATTERN dummydata EXCLUDE)
endmacro()

#
# hawaii_install_shell(shell srcpath dstpath)
#
# Installs a Hawaii System Preferences shell.
#
# \param shell the shell name (something like org.vendor.systempreferences)
# \param srcpath the source path to install from
#
macro(hawaii_install_shell shell srcpath)
    install(DIRECTORY ${srcpath}/
            DESTINATION ${DATA_INSTALL_DIR}/hawaii-system-preferences/shells/${shell}
            PATTERN .svn EXCLUDE
            PATTERN CMakeLists.txt EXCLUDE
            PATTERN Messages.sh EXCLUDE
            PATTERN dummydata EXCLUDE)
endmacro()
