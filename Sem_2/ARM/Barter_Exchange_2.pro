QT += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
win32 {
    LIBS += -lopengl32 -lglu32
}
TARGET = BarterApp
TEMPLATE = app
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    itemdialog.cpp \
    bartermodel.cpp \
    glwidget.cpp \
    trademanager.cpp \
    chainfinder.cpp \
    chaindialog.cpp \
    storage.cpp \
    graphwidget.cpp
HEADERS += \
    mainwindow.h \
    itemdialog.h \
    bartermodel.h \
    glwidget.h \
    trademanager.h \
    item.h \
    chainfinder.h \
    chaindialog.h \
    storage.h \
    graphwidget.h
