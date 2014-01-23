#-------------------------------------------------
#
# Project created by QtCreator 2013-12-31T15:21:02
#
#-------------------------------------------------

QT       += core gui

TARGET = CheckersGUI
TEMPLATE = app


SOURCES += \
    main.cpp \
    controller.cpp \
    draughtboard.cpp \
    draughtpiece.cpp \
    piece.cpp \
    clickablelabel.cpp

HEADERS  += \
    controller.h \
    draughtboard.h \
    draughtpiece.h \
    factory.h \
    piece.h \
    prototype.h \
    rules.h \
    clickablelabel.h

FORMS    +=

OTHER_FILES += \
    factory.ipp
