#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "setting.h"
#include "table.h"

typedef QMap<Setting::TblType, Table *> MapTbl;

class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    QMdiArea *mdiArea;

    MapTbl mapTbl;

    void CreateMenu();

private slots:
    void OpenTblSportsmen();
    void OpenTblTrainer();
    void OpenTblClub();

    bool IsOpen(Setting::TblType aTT);
    QMdiSubWindow *OpenTbl(Setting::TblType aTT, Table *aTbl);
    void CloseTable(QObject *aTbl);

public:
    MainWindow(QWidget *aParent = 0);
};

#endif // MAINWINDOW_H
