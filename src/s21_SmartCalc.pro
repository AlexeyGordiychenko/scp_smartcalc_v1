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
    s21_credit.c \
    s21_graphwindow.cpp \
    s21_smartcalc.c \
    s21_smartcalc_app.cpp

HEADERS += \
    qcustomplot.h \
    s21_credit.h \
    s21_graphwindow.h \
    s21_smartcalc.h \
    s21_smartcalc_app.h

FORMS += \
    s21_graphwindow.ui \
    s21_smartcalc_app.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
