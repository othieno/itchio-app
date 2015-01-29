# The project relies on features introduced in Qt 5.4.
#greaterThan(QT_MAJOR_VERSION, 4):greaterThan(QT_MINOR_VERSION, 3) {

# Include the necessary modules.
QT *= core gui widgets network sql

# Locate and include the OpenSSL package.
CONFIG *= link_pkgconfig
PKGCONFIG *= openssl

# Set build output directories.
DESTDIR      = .
OBJECTS_DIR  = $$DESTDIR/obj
MOC_DIR      = $$DESTDIR/moc
RCC_DIR      = $$DESTDIR/rcc
UI_DIR       = $$DESTDIR/ui

# Enable C++11 support and add compiler flags that promote extra error checking.
CONFIG *= c++11
QMAKE_CXXFLAGS *= -g -Wall -Wextra -Werror -pedantic-errors -ansi

# Use the clang compiler (for debug purposes).
#QMAKE_CXX = clang++-3.6

# Turn on debugging to enable features that are disabled when the QT_NO_DEBUG is set, e.g. Q_ASSERT.
CONFIG *= debug

#} else: error(The current Qt version ($$QT_VERSION) is unsupported. Please update your Qt installation to version 5.4 or later.)
