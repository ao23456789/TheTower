QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Monster.cpp \
    dialogelf.cpp \
    dialogmerchant.cpp \
    dialogprincess.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mine.cpp \
    note.cpp \
    one.cpp \
    one_ui.cpp \
    position.cpp \
    suduku.cpp \
    tower.cpp

HEADERS += \
    Monster.h \
    dialogelf.h \
    dialogmerchant.h \
    dialogprincess.h \
    mainwindow.h \
    map.h \
    mine.h \
    note.h \
    one.h \
    one_ui.h \
    position.h \
    suduku.h \
    tower.h

FORMS += \
    dialogelf.ui \
    dialogmerchant.ui \
    dialogprincess.ui \
    mainwindow.ui \
    note.ui \
    one_ui.ui \
    tower.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
