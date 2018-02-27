
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

RC_FILE     = info.rc

SOURCES += main.cpp
#-L/path/to -lpsapi
LIBS +=  -lws2_32
