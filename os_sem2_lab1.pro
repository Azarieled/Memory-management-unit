TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c99

SOURCES += main.c \
    mmu.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    mmu.h

