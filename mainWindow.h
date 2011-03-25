#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "setting.h"
#include "table.h"

typedef QMap<Setting::TblType, Table *> MapTable;

class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    QMdiArea *mdiArea;

    MapTable mapTbl;

    void CreateMenu();

private slots:
    void CreateTblSportsmen();
    void CreateTblTrainer();
    void CreateTblClub();
    bool IsOpen(TblType aTT);

public:
    MainWindow(QWidget *aParent = 0);
};

#endif // MAINWINDOW_H
