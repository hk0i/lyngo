######################################################################
# Automatically generated by qmake (2.01a) Thu Mar 10 15:12:33 2011
######################################################################

TEMPLATE = app
TARGET = grade
DEPENDPATH += .
INCLUDEPATH += . ..
unix { QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/.. }
LIBS += -L.. -llyngo
CONFIG += debug

# Input
SOURCES += grade.cpp
