QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/centralwidget/centralwidget.cc \
    \
    src/displaywidget/displaywidget.cc \
    src/displaywidget/paintevent_dw.cc \
    \
    src/gridwidget/getters_gw.cc \
    src/gridwidget/gridwidget.cc \
    src/gridwidget/mouseevents.cc \
    src/gridwidget/paintevent.cc \
    src/gridwidget/paintgrid.cc \
    src/gridwidget/setters_gw.cc \
    \
    src/mainwindow/mainwindow.cc\
    \
    src/menubar/menubar.cc \
    \
    src/spellswidget/spell/formatteddescription.cc \
    src/spellswidget/spell/getters.cc \
    src/spellswidget/spell/private.cc \
    src/spellswidget/spell/spell.cc \
    src/spellswidget/loadspells.cc \
    src/spellswidget/slots.cc \
    src/spellswidget/spellswidget.cc \
    \
    src/startupwindow/startupwindow.cc \
    \
    src/statusbar/statusbar.cc \
    \
    src/textwidget/textwidget.cc \
    \
    src/main.cc

HEADERS += \
    src/centralwidget/centralwidget.h \
    src/displaywidget/displaywidget.h \
    src/gridwidget/gridwidget.h \
    src/mainwindow/mainwindow.h \
    src/menubar/menubar.h \
    src/spellswidget/spell/spell.h \
    src/spellswidget/spellswidget.h \
    src/startupwindow/startupwindow.h \
    src/statusbar/statusbar.h \
    src/textwidget/textwidget.h

RESOURCES   +=  resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
