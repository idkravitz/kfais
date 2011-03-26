#include <QApplication>

#include "mainWindow.h"
#include "exceptions.h"

void Connect(const QString &dbname)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        throw Error(QObject::tr("���������� ������� ���� ������ ") + dbname);
    }
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec* codec =  QTextCodec::codecForName("cp1251");
    QTextCodec::setCodecForTr(codec);

    try
    {
        Connect(QObject::tr("db"));
    }
    catch(Error err)
    {
        QMessageBox::critical(0, QObject::tr("Error"), err.msg());
        return 1;
    }
    MainWindow *mw = new MainWindow;
    mw->show();

    return app.exec();
}
