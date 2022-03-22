TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Sources/BlCommands.c \
        Sources/BlReplyProcessing.c \
        Sources/WindowsSerialPort.c \
        Sources/fileops.c \
        Sources/utilities.c \
        main.c
INCLUDEPATH += Headers\

HEADERS += \
    Headers/WindowsSerialPort.h \
    Headers/main.h
