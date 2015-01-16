# This include file must be prepended to unit.pro and benchmark.pro, and NOT appended.

# Include the project file to get the current source code tree configuration.
!include(../itchio.pro) {
    error(Could not locate the source project file.)
}

# Prefix the include path directories.
# TODO Find out if this can be done faster with the ~= operator and regular expressions.
paths = $$INCLUDEPATH
INCLUDEPATH =
for (path, paths) {
    INCLUDEPATH += ../$$path
}

# Prefix the header files.
headers = $$HEADERS
HEADERS =
for (header, headers) {
    HEADERS += ../$$header
}

# Remove itchio.cpp since it creates an entry point conflict (two main functions), then prefix the source files.
SOURCES -= src/itchio.cpp
sources  = $$SOURCES
SOURCES  =
for (source, sources) {
    SOURCES += ../$$source
}

# Remove files that are not pertinent to the testing process.
FORMS =
RESOURCES =

# Add the testlib module.
QT += testlib
