#include <QApplication>

#include "setting.h"
#include "mainWindow.h"
#include "exceptions.h"

void Connect(const QString &dbname)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        throw Error(QObject::tr("Невозможно открыть базу данных ") + dbname);
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qApp->addLibraryPath("./plugins");
    QTextCodec* codec =  QTextCodec::codecForName("cp1251");
    QTextCodec::setCodecForTr(codec);

    Sett::LoadSettings();

    QApplication::setApplicationName("Kudo federation AIS");
    QApplication::setApplicationVersion("1.0");

    try
    {
        Connect("base.db");
    }
    catch(Error err)
    {
        QMessageBox::critical(Sett::GetMA(), Sett::GetErrMsgTitle(), err.msg());
        return 1;
    }

    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");

    MainWindow *mw = new MainWindow;
    mw->show();
    return app.exec();
}
