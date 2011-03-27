#include <QApplication>

#include "../headers/setting.h"
#include "../headers/mainWindow.h"
#include "../headers/exceptions.h"

using namespace Setting;

void InitSetting()
{
    Setting::mdiArea = new QMdiArea;
}

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

    QTextCodec* codec =  QTextCodec::codecForName("cp1251");
    QTextCodec::setCodecForTr(codec);

    QApplication::setApplicationName("Kudo federation AIS");
    QApplication::setApplicationVersion("1.0");

    try
    {
        InitSetting();
        Connect("base.db");
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
