QT += sql

CONFIG += qaxcontainer

SOURCES += \
    sources/table.cpp \
    sources/mainWindow.cpp \
    sources/main.cpp \
    sources/setting.cpp \
    sources/card.cpp \
    sources/reports.cpp \
    sources/tableModelView.cpp \
    sources/controlPanel.cpp

HEADERS += \
    headers/table.h \
    headers/setting.h \
    headers/mainWindow.h \
    headers/exceptions.h \
    headers/card.h \
    headers/reports.h \
    headers/tableModelView.h \
    headers/controlPanel.h

RESOURCES += \
    icons.qrc

INCLUDEPATH += headers/
