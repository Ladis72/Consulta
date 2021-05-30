QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    conexion.cpp \
    dbfunc.cpp \
    loggin.cpp \
    main.cpp \
    consulta.cpp

HEADERS += \
    conexion.h \
    consulta.h \
    dbfunc.h \
    loggin.h

FORMS += \
    consulta.ui \
    loggin.ui

TRANSLATIONS += \
    Consulta_es_ES.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    iconos.qrc