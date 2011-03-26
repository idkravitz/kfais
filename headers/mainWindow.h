#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../headers/setting.h"
#include "../headers/table.h"
#include "../headers/xmlreports.h"

typedef QMap<Setting::TblType, Table *> MapTbl;

class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    QMdiArea *mdiArea;
    ReportsMaker* reportsMaker;

    MapTbl mapTbl;

    void CreateMenu();

private slots:
    void OpenTblSportsmen();
    void OpenTblTrainer();
    void OpenTblClub();
    void GenerateReport();

    bool IsOpen(Setting::TblType aTT) const;
    QMdiSubWindow *OpenTbl(Setting::TblType aTT, Table *aTbl);
    void CloseTable(QObject *aTbl);

public:
    MainWindow(QWidget *aParent = 0);
};

#endif // MAINWINDOW_H
