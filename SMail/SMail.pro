#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T12:16:20
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMail
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    account.cpp \
    message.cpp

HEADERS  += mainwindow.h \
    account.h \
    message.h \
    openssl/ssl.h \
    openssl/err.h \
    base64.h \
    database.h \
    pop3.h \
    smtp.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    style.qss


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Built-OpenSSL-VC-64/lib/ -llibeay32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Built-OpenSSL-VC-64/lib/ -llibeay32

INCLUDEPATH += $$PWD/../../../../Built-OpenSSL-VC-64/include
DEPENDPATH += $$PWD/../../../../Built-OpenSSL-VC-64/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Built-OpenSSL-VC-64/lib/liblibeay32.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Built-OpenSSL-VC-64/lib/liblibeay32d.a
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Built-OpenSSL-VC-64/lib/libeay32.lib
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Built-OpenSSL-VC-64/lib/libeay32.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Built-OpenSSL-VC-64/lib/ -lssleay32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Built-OpenSSL-VC-64/lib/ -lssleay32

INCLUDEPATH += $$PWD/../../../../Built-OpenSSL-VC-64/include
DEPENDPATH += $$PWD/../../../../Built-OpenSSL-VC-64/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Built-OpenSSL-VC-64/lib/libssleay32.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Built-OpenSSL-VC-64/lib/libssleay32d.a
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Built-OpenSSL-VC-64/lib/ssleay32.lib
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Built-OpenSSL-VC-64/lib/ssleay32.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../mimetic-0.9.8/mimetic-0.9.8/win32/ -llibmimetic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../mimetic-0.9.8/mimetic-0.9.8/win32/ -llibmimetic

INCLUDEPATH += $$PWD/../../../mimetic-0.9.8/mimetic-0.9.8/win32
DEPENDPATH += $$PWD/../../../mimetic-0.9.8/mimetic-0.9.8/win32

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../mimetic-0.9.8/mimetic-0.9.8/win32/liblibmimetic.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../mimetic-0.9.8/mimetic-0.9.8/win32/liblibmimeticd.a
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../mimetic-0.9.8/mimetic-0.9.8/win32/libmimetic.lib
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../mimetic-0.9.8/mimetic-0.9.8/win32/libmimetic.lib
