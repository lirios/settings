#!/bin/bash

set -e

source /usr/local/share/liri-travis/functions

# Install dependencies
travis_start "install_packages"
msg "Install packages..."
dnf install -y \
     xkeyboard-config \
     polkit-devel \
     polkit-qt5-1-devel \
     libqtxdg-devel \
     libxcrypt-devel
travis_end "install_packages"

# Install artifacts
travis_start "artifacts"
msg "Install artifacts..."
for name in cmakeshared fluid libliri qtgsettings; do
    /usr/local/bin/liri-download-artifacts $TRAVIS_BRANCH ${name}-artifacts.tar.gz
done
travis_end "artifacts"

# Configure
travis_start "configure"
msg "Setup CMake..."
mkdir build
cd build
cmake .. \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DINSTALL_LIBDIR=/usr/lib64 \
    -DINSTALL_QMLDIR=/usr/lib64/qt5/qml \
    -DINSTALL_PLUGINSDIR=/usr/lib64/qt5/plugins
travis_end "configure"

# Build
travis_start "build"
msg "Build..."
make -j $(nproc)
travis_end "build"

# Install
travis_start "install"
msg "Install..."
make install
travis_end "install"
