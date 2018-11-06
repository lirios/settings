find_package(PkgConfig)

pkg_check_modules(Polkit polkit-gobject-1 REQUIRED IMPORTED_TARGET)
