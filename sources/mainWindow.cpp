#include "mainWindow.h"

MainWindow::MainWindow(QWidget *aParent):
        QMainWindow(aParent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowTitle("Kudo federation AIS");
    setCentralWidget(Sett::GetMA());
    setWindowIcon(QIcon(":/resource/Main.png"));

    CreateMenu();
}

void MainWindow::CreateMenu()
{
    QMenuBar *mnBar = new QMenuBar;
    setMenuBar(mnBar);

    QMenu *mnFile = new QMenu(tr("Файл"));
    mnFile->addAction(QIcon(":/resource/Exit.ico"), tr("Выход"), this, SLOT(close()));

    QMenu *mnAbout = new QMenu(tr("Помощь"));
    mnAbout->addAction(QIcon(":/resource/About.ico"), tr("О программе"), this, SLOT(OpenAbout()));

    QMenu *mnTables = new QMenu(tr("Таблицы"));
    mnTables->addAction(QIcon(":/resource/Sport.ico"), Sett::GetTblTitle(ttSport), this, SLOT(OpenTblSport()));
    mnTables->addAction(QIcon(":/resource/Coach.ico"), Sett::GetTblTitle(ttCoach), this, SLOT(OpenTblCoach()));
    mnTables->addAction(QIcon(":/resource/Club.ico"), Sett::GetTblTitle(ttClub), this, SLOT(OpenTblClub()));
    mnTables->addAction(QIcon(":/resource/Sert.ico"), Sett::GetTblTitle(ttSert), this, SLOT(OpenTblSert()));
    mnTables->addAction(QIcon(":/resource/Fee.ico"), Sett::GetTblTitle(ttFee), this, SLOT(OpenTblFee()));
    mnTables->addAction(QIcon(":/resource/SportComp.ico"), Sett::GetTblTitle(ttSportComp), this, SLOT(OpenTblSportComp()));
    mnTables->addAction(QIcon(":/resource/Comp.ico"), Sett::GetTblTitle(ttComp), this, SLOT(OpenTblComp()));
    mnTables->addAction(QIcon(":/resource/Categ.ico"), Sett::GetTblTitle(ttCateg), this, SLOT(OpenTblCateg()));
    mnTables->addAction(QIcon(":/resource/Rank.ico"), Sett::GetTblTitle(ttRank), this, SLOT(OpenTblRank()));
    mnTables->addAction(QIcon(":/resource/PrzWin.ico"), Sett::GetTblTitle(ttPrzWin), this, SLOT(OpenTblPrzWin()));

    QMenu *mnReports = new QMenu(tr("Отчеты"));
    mnReports->addAction(QIcon(":/resource/Report.ico"), Sett::GetRepTitle(rtSport), this, SLOT(OpenRepSport()));
    mnReports->addAction(QIcon(":/resource/Report.ico"), Sett::GetRepTitle(rtSert), this, SLOT(OpenRepSert()));
    mnReports->addAction(QIcon(":/resource/Report.ico"), Sett::GetRepTitle(rtDraw), this, SLOT(OpenRepDraw()));
    mnReports->addAction(QIcon(":/resource/Report.ico"), Sett::GetRepTitle(rtPulka), this, SLOT(OpenRepPulka()));
    mnReports->addAction(QIcon(":/resource/Report.ico"), Sett::GetRepTitle(rtResults), this, SLOT(OpenRepResults()));
    mnReports->addAction(QIcon(":/resource/Report.ico"), Sett::GetRepTitle(rtTechnical), this, SLOT(OpenRepTechnical()));

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

void MainWindow::OpenAbout()
{
    QMessageBox::about(this, tr("О программе"),
            tr("<h2>KFAIS v0.9</h2>"
               "<p>Все права защищены &copy; 2011 django.vl@gmail.com</p>"));
}
