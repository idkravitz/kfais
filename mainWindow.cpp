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
