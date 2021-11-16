QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS = -Wall -pedantic

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/centralwidget/centralwidget.cc \
    src/centralwidget/getters_cw.cc \
    \
    src/clientconnection/clientconnection.cc \
    src/clientconnection/connect_cc.cc \
    src/clientconnection/ondata_cc.cc \
    \
    src/connectdialog/connectdialog.cc \
    src/connectdialog/getentries.cc \
    src/connectdialog/onpress_cd.cc \
    \
    src/connectioncommon/readsocket.cc \
    src/connectioncommon/sendblob.cc \
    \
    src/displaywidget/displaycontrolwidget.cc \
    src/displaywidget/displaywidget.cc \
    src/displaywidget/getters_dcw.cc \
    src/displaywidget/paintevent_dw.cc \
    \
    src/gridcontrolwidget/gridcontrolwidget.cc \
    src/gridcontrolwidget/slots_gcw.cc \
    \
    src/gridwidget/avatar.cc \
    src/gridwidget/getters_gw.cc \
    src/gridwidget/gridwidget.cc \
    src/gridwidget/inputevents.cc \
    src/gridwidget/paintevent.cc \
    src/gridwidget/paintgrid.cc \
    src/gridwidget/paintline.cc \
    src/gridwidget/setters_gw.cc \
    \
    src/hostconnection/dispatch_hc.cc \
    src/hostconnection/onconnectionclosed.cc \
    src/hostconnection/hostconnection.cc \
    src/hostconnection/incomingconnections.cc \
    src/hostconnection/onincomingdata.cc \
    \
    src/mainwindow/connection_mw.cc \
    src/mainwindow/lines_mw.cc \
    src/mainwindow/mainwindow.cc \
    src/mainwindow/network.cc \
    src/mainwindow/onselectpressed.cc \
    \
    src/menubar/getters_mb.cc \
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
    src/statusbar/slots_sb.cc \
    src/statusbar/statusbar.cc \
    \
    src/textwidget/addtext.cc \
    src/textwidget/textwidget.cc \
    \
    src/userswidget/userswidget.cc \
    \
    src/utility/readfileb64.cc \
    \
    src/main.cc

HEADERS += \
    src/centralwidget/centralwidget.h \
    src/clientconnection/clientconnection.h \
    src/connectdialog/connectdialog.h \
    src/connectioncommon/connectioncommon.h \
    src/displaywidget/displaywidget.h \
    src/gridcontrolwidget/gridcontrolwidget.h \
    src/gridwidget/gridwidget.h \
    src/hostconnection/hostconnection.h \
    src/mainwindow/mainwindow.h \
    src/menubar/menubar.h \
    src/spellswidget/spell/spell.h \
    src/spellswidget/spellswidget.h \
    src/startupwindow/startupwindow.h \
    src/statusbar/statusbar.h \
    src/textwidget/textwidget.h \
    src/userswidget/userswidget.h \
    src/utility/utility.h

RESOURCES   +=  resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
