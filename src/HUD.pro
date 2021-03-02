QT += widgets websockets
CONFIG += c++11
TEMPLATE = app
TARGET = hud


LIBS += -L$$PWD/../lib \
    -lcsutils


INCLUDEPATH +=  \
    $$PWD/../include/csutils


HEADERS +=  \
    appwnd.h \
    hud.h \
    scalablewgt.h


SOURCES +=  \
    appwnd.cpp \
    hud.cpp \
    main.cpp \
    scalablewgt.cpp

RESOURCES += \
    res.qrc


