QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Rampi # nom du fichier .exe

VERSION = 1.0
QMAKE_TARGET_COMPANY = Varius Lab
QMAKE_TARGET_PRODUCT = Rampi
QMAKE_TARGET_DESCRIPTION = "Convertisseur d'angle et calculatrice trigonométrique pour les architectes"
QMAKE_TARGET_COPYRIGHT = Varvara Petrova 2023
RC_ICONS += ./img/Rampi96p.ico


SOURCES += \
    TriangleR.cpp \
    constants.cpp \
    main.cpp \
    RampCalculator.cpp

HEADERS += \
    RampCalculator.h \
    TriangleR.h \
    constants.h

FORMS += \
    RampCalculator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
