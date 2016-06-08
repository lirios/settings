System Preferences
==================

[![IRC Network](https://img.shields.io/badge/irc-freenode-blue.svg "IRC Freenode")](https://webchat.freenode.net/?channels=hawaii-desktop)
[![GitHub release](https://img.shields.io/github/release/hawaii-desktop/hawaii-system-preferences.svg)](https://github.com/hawaii-desktop/hawaii-system-preferences)
[![GitHub issues](https://img.shields.io/github/issues/hawaii-desktop/hawaii-system-preferences.svg)](https://github.com/hawaii-desktop/hawaii-system-preferences/issues)

System preferences for the Hawaii desktop environment.

## Dependencies

Qt >= 5.6.0 with at least the following modules is required:

* [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
* [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)
* [qtquickcontrols2](http://code.qt.io/cgit/qt/qtquickcontrols2.git)
* [qttools](http://code.qt.io/cgit/qt/qttools.git/)

The following modules and their dependencies are required:

* [ECM >= 1.4.0](http://quickgit.kde.org/?p=extra-cmake-modules.git)
* [greenisland](https://github.com/hawaii-desktop/greenisland)
* [libhawaii](https://github.com/hawaii-desktop/libhawaii)
* [polkit-qt5-1](https://quickgit.kde.org/?p=polkit-qt-1.git)
* [xkeyboard-config](https://cgit.freedesktop.org/xkeyboard-config/)

## Build and installation

Building this module is a piece of cake.

Assuming you are in the source directory, just create a build directory
and run cmake:

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/opt/hawaii ..
```

To do a debug build the last command can be:

```sh
cmake -DCMAKE_INSTALL_PREFIX=/opt/hawaii -DCMAKE_BUILD_TYPE=Debug ..
```

To do a release build instead it can be:

```sh
cmake -DCMAKE_INSTALL_PREFIX=/opt/hawaii -DCMAKE_BUILD_TYPE=Release ..
```

If not passed, the `CMAKE_INSTALL_PREFIX` parameter defaults to /usr/local.
You have to specify a path that fits your needs, /opt/hawaii is just an example.

The `CMAKE_BUILD_TYPE` parameter allows the following values:

* **Debug:** debug build
* **Release:** release build
* **RelWithDebInfo:** release build with debugging information

## Installation

It's really easy, it's just a matter of typing:

```sh
make install
```

from the build directory.

### System-wide installation

Those who want to perform a system-wide installation, such as package
maintainers, should pass different arguments to cmake:

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DKDE_INSTALL_USE_QT_SYS_PATHS=ON ..
```

Feel free to choose whatever `CMAKE_BUILD_TYPE` value you desire.

## Translations

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
