QT       += core gui
QT       += printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    qcustomplot.cpp \
    scp_credit.c \
    scp_graphwindow.cpp \
    scp_smartcalc.c \
    scp_smartcalc_app.cpp

HEADERS += \
    qcustomplot.h \
    scp_credit.h \
    scp_graphwindow.h \
    scp_smartcalc.h \
    scp_smartcalc_app.h

FORMS += \
    scp_graphwindow.ui \
    scp_smartcalc_app.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
