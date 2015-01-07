# This include file must be appended to src.pro, and NOT prepended.

# Add the necessary modules.
QT *= core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Resource files.
RESOURCES += $$BASEDIR/res/resources.qrc

# Change the locations of the built files.
DESTDIR      = .
OBJECTS_DIR  = $$DESTDIR/obj
MOC_DIR      = $$DESTDIR/moc
RCC_DIR      = $$DESTDIR/rcc
UI_DIR       = $$DESTDIR/ui

# Find the OpenSSL package.
CONFIG += link_pkgconfig
PKGCONFIG += openssl

# Turn on debugging to enable features that are disabled when the QT_NO_DEBUG is set, e.g. Q_ASSERT.
CONFIG += debug

# Add C++11 support.
CONFIG += c++11

# Add compiler flags for extra error checking.
QMAKE_CXXFLAGS += -Wall -Wextra -Werror -Wundef -Woverloaded-virtual #-Wshadow
