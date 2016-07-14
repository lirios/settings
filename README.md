Settings
========

[![ZenHub.io](https://img.shields.io/badge/supercharged%20by-zenhub.io-blue.svg)](https://zenhub.io)

[![License](https://img.shields.io/badge/license-GPLv2.0%2B-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)
[![GitHub release](https://img.shields.io/github/release/qmlos/settings.svg)](https://github.com/qmlos/settings)
[![Build Status](https://travis-ci.org/qmlos/settings.svg?branch=develop)](https://travis-ci.org/qmlos/settings)
[![GitHub issues](https://img.shields.io/github/issues/qmlos/settings.svg)](https://github.com/qmlos/settings/issues)
[![Maintained](https://img.shields.io/maintenance/yes/2016.svg)](https://github.com/qmlos/settings/commits/develop)

Settings application and modules for qmlOS.

### Dependencies

Qt >= 5.7.0 with at least the following modules is required:

* [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
* [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)
* [qtquickcontrols2](http://code.qt.io/cgit/qt/qtquickcontrols2.git)
* [qttools](http://code.qt.io/cgit/qt/qttools.git/)

The following modules and their dependencies are required:

* [ECM >= 1.7.0](http://quickgit.kde.org/?p=extra-cmake-modules.git)
* [greenisland](https://github.com/hawaii-desktop/greenisland)
* [libhawaii](https://github.com/hawaii-desktop/libhawaii)
* [polkit-qt5-1](https://quickgit.kde.org/?p=polkit-qt-1.git)
* [xkeyboard-config](https://cgit.freedesktop.org/xkeyboard-config/)

### Installation

From the root of the repository, run:

```sh
mkdir build; cd build
cmake .. -DKDE_INSTALL_USE_QT_SYS_PATHS=ON
make
make install # use sudo if necessary
```

On the `cmake` line, you can specify additional configuration parameters:

 * `-DCMAKE_INSTALL_PREFIX=/path/to/install` (for example, `/opt/qmlos` or `/usr`)
 * `-DCMAKE_BUILD_TYPE=<build_type>`, where `<build_type>` is one of:
   * **Debug:** debug build
   * **Release:** release build
   * **RelWithDebInfo:** release build with debugging information

### Translations

We use Transifex to translate this project, please submit your
translations [here](https://www.transifex.com/hawaii/system-preferences/dashboard/).

Developers can refresh translations with the `-DUPDATE_TRANSLATIONS` argument to cmake
and then upload the sources to Transifex with:

```sh
tx push -s
```

New translations can be pulled from Transifex with:

```sh
tx pull -s --minimum-perc=10
```

### Licensing

Settings is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.
