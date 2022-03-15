QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CompositionProcessing.cpp \
    GreyScaleProcessing.cpp \
    main.cpp \
    mainwindow.cpp \
    svgview.cpp

HEADERS += \
    CompositionProcessing.h \
    GreyScaleProcessing.h \
    ImageProcessing.h \
    mainwindow.h \
    svgview.h

QT           += widgets svg svgwidgets

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    ImageProcessor_en_DE.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Resources.qrc
