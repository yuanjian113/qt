TEMPLATE = app
TARGET = QSimpleDownloader
QT += core \
    gui \
    network \
    xml
HEADERS += src/OptionDlg.h \
    src/JobScheduler.h \
    src/HtmlParser.h \
    src/HttpGet.h \
    src/QSimpleDownloader.h \
    src/Target.h
SOURCES += src/OptionDlg.cpp \
    src/JobScheduler.cpp \
    src/HtmlParser.cpp \
    src/HttpGet.cpp \
    src/Main.cpp \
    src/QSimpleDownloader.cpp
FORMS += 
RESOURCES += 
CONFIG += release
include(D:\Qt\log4qt\src\log4qt\log4qt.pri)
