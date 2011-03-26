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

void MainWindow::CreateMenu()
{
    QMenuBar *mnBar = new QMenuBar;
    setMenuBar(mnBar);

    QMenu *mnFile = new QMenu(tr("Файл"));
    QAction *actExit = mnFile->addAction(tr("Выход"), this, SLOT(close()));

    QMenu *mnAbout = new QMenu(tr("Помощь"));
    QAction *actAbout = mnAbout->addAction(tr("О программе"));

    QMenu *mnTables = new QMenu(tr("Таблицы"));
    QAction *actSportmen = mnTables->addAction(tr("Спортсмены"), this, SLOT(OpenTblSportsmen()));
    QAction *actTrainer = mnTables->addAction(tr("Тренеры"), this, SLOT(OpenTblTrainer()));
    QAction *actClub = mnTables->addAction(tr("Клубы"), this, SLOT(OpenTblClub()));

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

void MainWindow::OpenTblSportsmen()
{
    if (!IsOpen(ttSportsmen))
    {
        QMdiSubWindow *sw = OpenTbl(ttSportsmen, new TblSportsmen(mdiArea));
    }
}

void MainWindow::OpenTblTrainer()
{
    if (!IsOpen(ttTrainer))
    {
        QMdiSubWindow *sw = OpenTbl(ttTrainer, new TblTrainer(mdiArea));
    }
}

void MainWindow::OpenTblClub()
{
    if (!IsOpen(ttClub))
    {
        QMdiSubWindow *sw = OpenTbl(ttClub, new TblClub(mdiArea));
    }
}
