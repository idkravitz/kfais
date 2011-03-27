#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "setting.h"
#include "table.h"

typedef QMap<TblType, Table *> MapTbl;

class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    MapTbl mapTbl;

    void CreateMenu();

private slots:
    void OpenTblSport();
    void OpenTblCoach();
    void OpenTblClub();
    void OpenTblSert();
    void OpenTblFee();
    void OpenTblSportComp();
    void OpenTblComp();
    void OpenTblCateg();
    void OpenTblRank();

    bool IsOpen(TblType aTT) const;
    QMdiSubWindow *OpenTbl(TblType aTT, Table *aTbl);
    void CloseTable(QObject *aTbl);

public:
    MainWindow(QWidget *aParent = 0);
};

#endif // MAINWINDOW_H
