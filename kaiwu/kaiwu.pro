TEMPLATE = lib
CONFIG += console staticlib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += debug_and_release
LIBS += -lpthread
VERSION = 1.0
DESTDIR = ../build/

CONFIG(debug, debug|release) {
    TARGET = kaiwud
}else{
    TARGET = kaiwu
}

TARGET = $$sprintf(%1-%2, $$TARGET, $$VERSION)

copy_head_file.target = .copy_head_file
copy_head_file.commands += mkdir -p ../build/inc
copy_head_file.commands += && cp *.h ../build/inc/

QMAKE_EXTRA_TARGETS += copy_head_file
POST_TARGETDEPS += .copy_head_file

HEADERS += \
    condition.h \
    count_down_latch.h \
    file_appender.h \
    file_basename.h \
    file_reader.h \
    fixed_buffer.h \
    fmt.h \
    log.h \
    log_file.h \
    mutex.h \
    process_info.h \
    shared_lib.h \
    singleton.h \
    string_arg.h \
    string_type.h \
    thread.h \
    thread_info.h \
    thread_pool.h

SOURCES += \
    count_down_latch.cc \
    file_appender.cc \
    file_reader.cc \
    log.cc \
    log_file.cc \
    process_info.cc \
    thread.cc \
    thread_info.cc \
    thread_pool.cc

OTHER_FILES += \
    zbuild.sh
