#include "../headers/mainWindow.h"

using namespace Setting;

MainWindow::MainWindow(QWidget *aParent):
        QMainWindow(aParent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowTitle("Kudo federation AIS");
    setCentralWidget(mdiArea);

    CreateMenu();
}

void MainWindow::CreateMenu()
{
    QMenuBar *mnBar = new QMenuBar;
    setMenuBar(mnBar);

    QMenu *mnFile = new QMenu(tr("Файл"));
    mnFile->addAction(tr("Выход"), this, SLOT(close()));

    QMenu *mnAbout = new QMenu(tr("Помощь"));
    mnAbout->addAction(tr("О программе"));

    QMenu *mnTables = new QMenu(tr("Таблицы"));
    using namespace Setting;
    mnTables->addAction(tr(table_settings[ttSport].title), this, SLOT(OpenTblSport()));
    mnTables->addAction(tr(table_settings[ttCoach].title), this, SLOT(OpenTblCoach()));
    mnTables->addAction(tr(table_settings[ttClub].title), this, SLOT(OpenTblClub()));
    mnTables->addAction(tr(table_settings[ttSert].title), this, SLOT(OpenTblSert()));
    mnTables->addAction(tr(table_settings[ttFee].title), this, SLOT(OpenTblFee()));
    mnTables->addAction(tr(table_settings[ttSportComp].title), this, SLOT(OpenTblSportComp()));
    mnTables->addAction(tr(table_settings[ttComp].title), this, SLOT(OpenTblComp()));
    mnTables->addAction(tr(table_settings[ttCateg].title), this, SLOT(OpenTblCateg()));

    mnBar->addMenu(mnFile);
    mnBar->addMenu(mnTables);
    mnBar->addMenu(mnAbout);
}

bool MainWindow::IsOpen(TblType aTT) const
{
    MapTbl::const_iterator it = mapTbl.find(aTT);
    if (it == mapTbl.end())
    {
        return false;
    }
    it.value()->setFocus();
    return true;
}

QMdiSubWindow *MainWindow::OpenTbl(TblType aTT, Table *aTbl)
{
    QMdiSubWindow *sw = mdiArea->addSubWindow(aTbl);
    sw->show();
    mapTbl.insert(aTT, aTbl);
    connect(aTbl, SIGNAL(destroyed(QObject *)), this, SLOT(CloseTable(QObject *)));
    return sw;
}

void MainWindow::CloseTable(QObject *aTbl)
{
    MapTbl::iterator it = mapTbl.find(static_cast<Table *>(aTbl)->Type());
    if (it != mapTbl.end())
    {
        mapTbl.erase(it);
    }
}

void MainWindow::OpenTblSport()
{
    if (!IsOpen(ttSport))
    {
        QMdiSubWindow *sw = OpenTbl(ttSport, new TblSport(mdiArea));
    }
}

void MainWindow::OpenTblCoach()
{
    if (!IsOpen(ttCoach))
    {
        QMdiSubWindow *sw = OpenTbl(ttCoach, new TblCoach(mdiArea));
    }
}

void MainWindow::OpenTblClub()
{
    if (!IsOpen(ttClub))
    {
        QMdiSubWindow *sw = OpenTbl(ttClub, new TblClub(mdiArea));
    }
}

void MainWindow::OpenTblSert()
{
    if (!IsOpen(ttSert))
    {
        QMdiSubWindow *sw = OpenTbl(ttSert, new TblSert(mdiArea));
    }
}

void MainWindow::OpenTblFee()
{
    if (!IsOpen(ttFee))
    {
        QMdiSubWindow *sw = OpenTbl(ttFee, new TblFee(mdiArea));
    }
}

void MainWindow::OpenTblSportComp()
{
    if (!IsOpen(ttSportComp))
    {
        QMdiSubWindow *sw = OpenTbl(ttSportComp, new TblSportComp(mdiArea));
    }
}

void MainWindow::OpenTblComp()
{
    if (!IsOpen(ttComp))
    {
        QMdiSubWindow *sw = OpenTbl(ttComp, new TblComp(mdiArea));
    }
}


void MainWindow::OpenTblCateg()
{
    if (!IsOpen(ttCateg))
    {
        QMdiSubWindow *sw = OpenTbl(ttCateg, new TblCateg(mdiArea));
    }
}
