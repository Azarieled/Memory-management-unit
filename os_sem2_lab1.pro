TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c99

SOURCES += src/main.c \
    src/os.c \
    src/mmu.c \
    src/processor.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    src/os.h \
    src/mmu.h \
    src/processor.h

