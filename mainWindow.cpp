#include "mainWindow.h"

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

    QMenu *mnFile = new QMenu(tr("����"));
    QAction *actExit = mnFile->addAction(tr("�����"), this, SLOT(close()));

    QMenu *mnAbout = new QMenu(tr("������"));
    QAction *actAbout = mnAbout->addAction(tr("� ���������"));

    QMenu *mnTables = new QMenu(tr("�������"));
    QAction *actSportmen = mnTables->addAction(tr("����������"), this, SLOT(OpenTblSportsmen()));
    QAction *actTrainer = mnTables->addAction(tr("�������"), this, SLOT(OpenTblTrainer()));
    QAction *actClub = mnTables->addAction(tr("�����"), this, SLOT(OpenTblClub()));

    mnBar->addMenu(mnFile);
    mnBar->addMenu(mnTables);
    mnBar->addMenu(mnAbout);
}

bool MainWindow::IsOpen(TblType aTT)
{

}

void MainWindow::OpenTblSportsmen()
{
    if (!IsOpen)
    {

    }
}

void MainWindow::OpenTblTrainer()
{

}

void MainWindow::OpenTblClub()
{

}
