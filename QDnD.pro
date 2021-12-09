QT       += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17
QMAKE_CXXFLAGS = -Wall -pedantic


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=  src/control/applicationcontrol.cc \
            src/control/entitymanager.cc \
            src/control/playercontrol.cc \
            \
            src/expressions/diceexpression.cc \
            src/expressions/diceparser.cc \
            src/expressions/dicetokenizer.cc \
            src/expressions/parserstate.cc \
            \
            src/model/entity.cc \
            src/model/griditemgroup.cc \
            src/model/gridmodel.cc \
            src/model/pixmapcache.cc \
            src/model/player.cc \
            src/model/spell.cc \
            \
            src/network/clientconnection.cc \
            src/network/connectionbase.cc \
            src/network/messagebuilder.cc \
            src/network/serverconnection.cc \
            \
            src/utility/enums.cc \
            src/utility/htmlformatting.cc \
            src/utility/loading.cc \
            src/utility/painting.cc \
            \
            src/view/chatwidget.cc \
            src/view/colordisplay.cc \
            src/view/connectdialog.cc \
            src/view/displaywidget.cc \
            src/view/dropwidget.cc \
            src/view/entitywidget.cc \
            src/view/mainwindow.cc \
            src/view/menubar.cc \
            src/view/playerswidget.cc \
            src/view/spellswidget.cc \
            src/view/statusbar.cc \
            \
            src/main.cc


HEADERS +=  src/control/applicationcontrol.h \
            src/control/entitymanager.h \
            src/control/playercontrol.h \
            \
            src/expressions/diceexpression.h \
            src/expressions/diceparser.h \
            src/expressions/dicetokenizer.h \
            src/expressions/parserstate.h \
            \
            src/model/entity.h \
            src/model/griditemgroup.h \
            src/model/gridmodel.h \
            src/model/pixmapcache.h \
            src/model/player.h \
            src/model/spell.h \
            \
            src/network/clientconnection.h \
            src/network/connectionbase.h \
            src/network/messagebuilder.h \
            src/network/serverconnection.h \
            \
            src/utility/enums.h \
            src/utility/htmlformatting.h \
            src/utility/loading.h \
            src/utility/painting.h \
            \
            src/view/chatwidget.h \
            src/view/colordisplay.h \
            src/view/connectdialog.h \
            src/view/displaywidget.h \
            src/view/dropwidget.h \
            src/view/entitywidget.h \
            src/view/mainwindow.h \
            src/view/menubar.h \
            src/view/playerswidget.h \
            src/view/spellswidget.h \
            src/view/statusbar.h


RESOURCES   +=  resources.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
