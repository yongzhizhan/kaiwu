TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
DESTDIR = ../build/
LIBS += -lgtest -lpthread
LIBS += -L../build/ -lkaiwud-1.0
INCLUDEPATH += ../build/inc/

SOURCES += \
    condition_test.cc \
    count_down_latch_test.cc \
    file_basename_test.cc \
    file_reader_test.cc \
    fmt_test.cc \
    io_test.cc \
    log_test.cc \
    mutex_test.cc \
    singleton_test.cc \
    thread_pool_test.cc \
    thread_test.cc \
    main.cc

