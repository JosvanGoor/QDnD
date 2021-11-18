QT       += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17
QMAKE_CXXFLAGS = -Wall -pedantic


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=  src/control/applicationcontrol.cc \
            \
            src/model/pixmapcache.cc \
            src/model/runtimemodel.cc \
            src/model/spell.cc \
            \
            src/utility/htmlformatting.cc \
            src/utility/loading.cc \
            \
            src/view/chatwidget.cc \
            src/view/mainwindow.cc \
            src/view/spellswidget.cc \
            \
            src/main.cc


HEADERS +=  src/control/applicationcontrol.h \
            \
            src/model/pixmapcache.h \
            src/model/runtimemodel.h \
            src/model/spell.h \
            \
            src/utility/htmlformatting.h \
            src/utility/loading.h \
            \
            src/view/chatwidget.h \
            src/view/mainwindow.h \
            src/view/spellswidget.h


RESOURCES   +=  resources.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
