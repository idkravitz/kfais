QT += sql

SOURCES += \
    sources/table.cpp \
    sources/mainWindow.cpp \
    sources/main.cpp \
    sources/setting.cpp \
    sources/card.cpp \
    sources/reports.cpp

HEADERS += \
    headers/table.h \
    headers/setting.h \
    headers/mainWindow.h \
    headers/exceptions.h \
    headers/card.h \
    headers/reports.h

RESOURCES += \
    icons.qrc

INCLUDEPATH += headers/
