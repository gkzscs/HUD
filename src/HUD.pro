QT += widgets websockets
CONFIG += c++11
TEMPLATE = app
TARGET = hud


LIBS += -L$$PWD/../lib \
    -lcsutils


INCLUDEPATH +=  \
    $$PWD/../include/csutils


HEADERS +=  \
    appwnd.h


SOURCES +=  \
    appwnd.cpp \
    main.cpp


