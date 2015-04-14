TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c99

SOURCES += src/main.c \
    src/mmu.c \
    src/processor.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    src/mmu.h \
    src/processor.h

