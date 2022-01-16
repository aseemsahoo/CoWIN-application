QT       += core gui sql
QT += widgets
CONFIG += resources_big
QMAKE_CXXFLAGS += -O0

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    AdminDialog1.cpp \
    Login.cpp \
    UserDialog1.cpp \
    main.cpp \
    user.cpp

HEADERS += \
    AdminDialog1.h \
    Login.h \
    UserDialog1.h \
    user.h

FORMS += \
    AdminDialog1.ui \
    Login.ui \
    UserDialog1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
