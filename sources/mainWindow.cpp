#include "mainWindow.h"

MainWindow::MainWindow(QWidget *aParent):
        QMainWindow(aParent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowTitle("Kudo federation AIS");
    setCentralWidget(Sett::GetMA());

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
    mnTables->addAction(Sett::GetTblTitle(ttSport), this, SLOT(OpenTblSport()));
    mnTables->addAction(Sett::GetTblTitle(ttCoach), this, SLOT(OpenTblCoach()));
    mnTables->addAction(Sett::GetTblTitle(ttClub), this, SLOT(OpenTblClub()));
    mnTables->addAction(Sett::GetTblTitle(ttSert), this, SLOT(OpenTblSert()));
    mnTables->addAction(Sett::GetTblTitle(ttFee), this, SLOT(OpenTblFee()));
    mnTables->addAction(Sett::GetTblTitle(ttSportComp), this, SLOT(OpenTblSportComp()));
    mnTables->addAction(Sett::GetTblTitle(ttComp), this, SLOT(OpenTblComp()));
    mnTables->addAction(Sett::GetTblTitle(ttCateg), this, SLOT(OpenTblCateg()));
    mnTables->addAction(Sett::GetTblTitle(ttRank), this, SLOT(OpenTblRank()));
    mnTables->addAction(Sett::GetTblTitle(ttPrzWin), this, SLOT(OpenTblPrzWin()));

    QMenu *mnReports = new QMenu(tr("Отчеты"));
    mnReports->addAction(Sett::GetRepTitle(rtSport), this, SLOT(OpenRepSport()));
    mnReports->addAction(Sett::GetRepTitle(rtSert), this, SLOT(OpenRepSert()));
    mnReports->addAction(Sett::GetRepTitle(rtDraw), this, SLOT(OpenRepDraw()));
    mnReports->addAction(Sett::GetRepTitle(rtPulka), this, SLOT(OpenRepPulka()));
    mnReports->addAction(Sett::GetRepTitle(rtResults), this, SLOT(OpenRepResults()));
    mnReports->addAction(Sett::GetRepTitle(rtTechnical), this, SLOT(OpenRepTechnical()));

    mnBar->addMenu(mnFile);
    mnBar->addMenu(mnTables);
    mnBar->addMenu(mnReports);
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
    QMdiSubWindow *sw = Sett::GetMA()->addSubWindow(aTbl);
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
        OpenTbl(ttSport, new TblSport(Sett::GetMA()));
    }
}

void MainWindow::OpenTblCoach()
{
    if (!IsOpen(ttCoach))
    {
        OpenTbl(ttCoach, new TblCoach(Sett::GetMA()));
    }
}

void MainWindow::OpenTblClub()
{
    if (!IsOpen(ttClub))
    {
        OpenTbl(ttClub, new TblClub(Sett::GetMA()));
    }
}

void MainWindow::OpenTblSert()
{
    if (!IsOpen(ttSert))
    {
        OpenTbl(ttSert, new TblSert(Sett::GetMA()));
    }
}

void MainWindow::OpenTblFee()
{
    if (!IsOpen(ttFee))
    {
        OpenTbl(ttFee, new TblFee(Sett::GetMA()));
    }
}

void MainWindow::OpenTblSportComp()
{
    if (!IsOpen(ttSportComp))
    {
        OpenTbl(ttSportComp, new TblSportComp(Sett::GetMA()));
    }
}

void MainWindow::OpenTblComp()
{
    if (!IsOpen(ttComp))
    {
        OpenTbl(ttComp, new TblComp(Sett::GetMA()));
    }
}


void MainWindow::OpenTblCateg()
{
    if (!IsOpen(ttCateg))
    {
        OpenTbl(ttCateg, new TblCateg(Sett::GetMA()));
    }
}

void MainWindow::OpenTblRank()
{
    if (!IsOpen(ttRank))
    {
        OpenTbl(ttRank, new TblRank(Sett::GetMA()));
    }
}

void MainWindow::OpenTblPrzWin()
{
    if (!IsOpen(ttPrzWin))
    {
        OpenTbl(ttPrzWin, new TblPrzWin(Sett::GetMA()));
    }
}

QMdiSubWindow *MainWindow::OpenRep(RepType aTT, Report *aRep)
{
    QMdiSubWindow *sw = Sett::GetMA()->addSubWindow(aRep);
    sw->show();
    return sw;
}

void MainWindow::OpenRepSport()
{
    OpenRep(rtSport, new RepSport(Sett::GetMA()));
}

void MainWindow::OpenRepSert()
{
    OpenRep(rtSert, new RepSert(Sett::GetMA()));
}

void MainWindow::OpenRepDraw()
{
    OpenRep(rtDraw, new RepDraw(Sett::GetMA()));
}

void MainWindow::OpenRepPulka()
{
    OpenRep(rtDraw, new RepPulka(Sett::GetMA()));
}

void MainWindow::OpenRepResults()
{
    OpenRep(rtDraw, new RepResults(Sett::GetMA()));
}

void MainWindow::OpenRepTechnical()
{
    OpenRep(rtDraw, new RepTechnical(Sett::GetMA()));
}
