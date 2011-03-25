#include <QApplication>

#include "mainWindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec* codec =  QTextCodec::codecForName("cp1251");
    QTextCodec::setCodecForTr(codec);

    MainWindow *mw = new MainWindow;
    mw->show();

    return app.exec();
}
