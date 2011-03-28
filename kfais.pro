QT += sql xml xmlpatterns

SOURCES += \
    sources/table.cpp \
    sources/mainWindow.cpp \
    sources/main.cpp \
    sources/xmlreports.cpp \
    sources/setting.cpp \
    sources/card.cpp

HEADERS += \
    headers/table.h \
    headers/setting.h \
    headers/mainWindow.h \
    headers/exceptions.h \
    headers/xmlreports.h \
    headers/card.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lxml2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lxml2
else:unix:!symbian: LIBS += -L$$PWD/../../../../usr/lib/ -lxml2

INCLUDEPATH += $$PWD/../../../../usr/include/libxml2
DEPENDPATH += $$PWD/../../../../usr/include/libxml2

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lxslt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lxslt
else:symbian: LIBS += -lxslt
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lxslt

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include
