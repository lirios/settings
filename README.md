System Preferences
==================

[![IRC Network](https://img.shields.io/badge/irc-freenode-blue.svg "IRC Freenode")](https://webchat.freenode.net/?channels=hawaii-desktop)
[![GitHub release](https://img.shields.io/github/release/hawaii-desktop/hawaii-system-preferences.svg)](https://github.com/hawaii-desktop/hawaii-system-preferences)
[![GitHub issues](https://img.shields.io/github/issues/hawaii-desktop/hawaii-system-preferences.svg)](https://github.com/hawaii-desktop/hawaii-system-preferences/issues)

System preferences for the Hawaii desktop environment.

## Dependencies

You need the following modules and their dependencies:

* [hawaii-shell](https://github.com/hawaii-desktop/hawaii-shell)

Make sure you also have Qt 5.4 or better with the following modules:

* qtbase
* qtdeclarative
* qtquickcontrols

Other dependencies:

* polkit-qt5-1
* xkeyboard-config

Optional dependencies:

* libkscreen

Build time dependencies:

* qttools

## Build

Building System Preferences is a piece of cake.

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

Package maintainers would pass `-DCMAKE_INSTALL_PREFIX=/usr`.

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
