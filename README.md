Settings
========

[![License](https://img.shields.io/badge/license-GPLv3.0%2B-blue.svg)](https://www.gnu.org/licenses/gpl-3.0.html)
[![GitHub release](https://img.shields.io/github/release/lirios/settings.svg)](https://github.com/lirios/settings)
[![GitHub issues](https://img.shields.io/github/issues/lirios/settings.svg)](https://github.com/lirios/settings/issues)
[![CI](https://github.com/lirios/settings/workflows/CI/badge.svg?branch=develop)](https://github.com/lirios/settings/actions?query=workflow%3ACI)

Settings application and modules for Liri desktop.

## Dependencies

Qt >= 6.6.0 with at least the following modules is required:

 * [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
 * [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)
 * [qttools](http://code.qt.io/cgit/qt/qttools.git)

The following modules and their dependencies are required:

 * [cmake](https://gitlab.kitware.com/cmake/cmake) >= 3.19.0
 * [cmake-shared](https://github.com/lirios/cmake-shared.git) >= 1.0.0
 * [qtaccountsservice](https://github.com/lirios/qtaccountsservice.git) >= 2.0.0
 * [qtgsettings](https://github.com/lirios/qtgsettings) >= 2.0.0
 * [fluid](https://github.com/lirios/fluid.git) >= 1.0.0
 * [libliri](https://github.com/lirios/libliri.git)
 * [polkit](https://cgit.freedesktop.org/polkit/)
 * [xkeyboard-config](https://cgit.freedesktop.org/xkeyboard-config)

## Installation

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/path/to/prefix ..
make
make install # use sudo if necessary
```

Replace `/path/to/prefix` to your installation prefix.
Default is `/usr/local`.

## Translations

We use Transifex to translate this project, please submit your
translations [here](https://www.transifex.com/lirios/liri-settings/dashboard/).

```sh
tx push -s
```

New translations can be pulled from Transifex with:

```sh
tx pull -s --minimum-perc=10
```

## Licensing

Licensed under the terms of the GNU General Public License version 3 or,
at your option, any later version.
