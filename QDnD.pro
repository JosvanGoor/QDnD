QT       += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17
QMAKE_CXXFLAGS = -Wall -pedantic


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=  src/expressions/diceexpression.cc \
            src/expressions/diceparser.cc \
            src/expressions/dicetokenizer.cc \
            src/expressions/parserstate.cc \
            \
            src/model/griditemgroup.cc \
            src/model/gridmodel.cc \
            src/model/pixmapcache.cc \
            src/model/runtimemodel.cc \
            src/model/spell.cc \
            \
            src/utility/enums.cc \
            src/utility/htmlformatting.cc \
            src/utility/loading.cc \
            \
            src/view/chatwidget.cc \
            src/view/connectdialog.cc \
            src/view/displaywidget.cc \
            src/view/dropwidget.cc \
            src/view/gridwidget.cc \
            src/view/mainwindow.cc \
            src/view/menubar.cc \
            src/view/playerswidget.cc \
            src/view/spellswidget.cc \
            src/view/statusbar.cc \
            \
            src/main.cc


HEADERS +=  src/expressions/diceexpression.h \
            src/expressions/diceparser.h \
            src/expressions/dicetokenizer.h \
            src/expressions/parserstate.h \
            \
            src/model/griditemgroup.h \
            src/model/gridmodel.h \
            src/model/pixmapcache.h \
            src/model/runtimemodel.h \
            src/model/spell.h \
            \
            src/utility/enums.h \
            src/utility/htmlformatting.h \
            src/utility/loading.h \
            \
            src/view/chatwidget.h \
            src/view/connectdialog.h \
            src/view/displaywidget.h \
            src/view/dropwidget.h \
            src/view/gridwidget.h \
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
