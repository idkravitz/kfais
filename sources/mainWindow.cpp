#include "../headers/mainWindow.h"

using namespace Setting;

MainWindow::MainWindow(QWidget *aParent):
        QMainWindow(aParent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    mdiArea = new QMdiArea;

    setWindowTitle("Kudo federation AIS");
    setCentralWidget(mdiArea);

    CreateMenu();
}

void MainWindow::GenerateReport()
{
    reportsMaker->MakeReport(tr("select * from sportsmen"));
}

void MainWindow::CreateMenu()
{
    QMenuBar *mnBar = new QMenuBar;
    setMenuBar(mnBar);

    reportsMaker = new ReportsMaker;

    QMenu *mnFile = new QMenu(tr("����"));
    mnFile->addAction(tr("�����"), this, SLOT(close()));

    QMenu *mnAbout = new QMenu(tr("������"));
    mnAbout->addAction(tr("� ���������"));

    QMenu *mnTables = new QMenu(tr("�������"));
    mnTables->addAction(tr(Sport::title), this, SLOT(OpenTblSport()));
    mnTables->addAction(tr(Coach::title), this, SLOT(OpenTblCoach()));
    mnTables->addAction(tr(Club::title), this, SLOT(OpenTblClub()));
    mnTables->addAction(tr(Sert::title), this, SLOT(OpenTblSert()));
    mnTables->addAction(tr(Fee::title), this, SLOT(OpenTblFee()));
    mnTables->addAction(tr(SportComp::title), this, SLOT(OpenTblSportComp()));
    mnTables->addAction(tr(Comp::title), this, SLOT(OpenTblComp()));
    mnTables->addAction(tr(Categ::title), this, SLOT(OpenTblCateg()));

    QAction *actSportsmenReport = mnBar->addAction(tr("�����"), this, SLOT(GenerateReport()));


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
