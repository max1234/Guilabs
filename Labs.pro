QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Labs
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    md5.cpp \
    ripemd.cpp \
    sha1.cpp \
    algorithms.cpp \
    elgamal.cpp \
    rsa.cpp


HEADERS  += dialog.h \
    md5.h \
    ripemd.h \
    sha1.h \
    algorithms.h \
    elgamal.h \
    rsa.h

FORMS    += dialog.ui

win32: LIBS += -L$$PWD/ -llibgmp-3
unix:  LIBS+= -lgmp
