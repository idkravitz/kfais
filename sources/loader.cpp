#import "loader.h"

/******************************* CSV parser *******************************/

ParserCSV::ParserCSV()
{
    //Empty
}

QString ParserCSV::TrimItemCSV(const QString &aItem)
{
    QString item = aItem.simplified();
    if(!item.isEmpty() && (item[0] == QChar('"')))
        item.remove(0,1);
    if(!item.isEmpty() && (item[item.size()-1] == QChar('"')))
        item.remove(item.count()-1,1);
    if(!item.isEmpty())
        item = item.replace("\"\"","\"");
    return item;
}

QList<QStringList> ParserCSV::ParseFile(const QString &aFileName, const QChar &aSeparator, unsigned int aColCount)
{
    QFile file(aFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw Error(tr("Невозможно открыть файл для чтения!"));

    QList<QStringList> resList;
    QStringList itemList;
    QString item;
    bool isQuote = false;

    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("cp1251"));
    while (!in.atEnd())
    {
        QString line = in.readLine().simplified();
        unsigned int count = line.size();
        for (unsigned int i = 0; i < count; ++i)
        {
            if (line[i] == QChar('"')) isQuote = !isQuote;
            if ((!isQuote) && (line[i] == aSeparator))
            {
                itemList.append(TrimItemCSV(item));
                item = "";
            }
            else
            {
                item += line[i];
            }
            if ((count - 1 == i) && (!isQuote))
            {
                itemList.append(TrimItemCSV(item));
                if (itemList.size() && itemList.size() != aColCount)
                    throw Error(tr("Некорректный формат файла"));
                resList.append(itemList);
                itemList.clear();
                item = "";
            }
        }
    }
    file.close();
    return resList;
}

/******************************* Basic class for loading *******************************/

Loader::Loader(QWidget *aParent, const QString &aTitle):
    QDialog(aParent),
    isReadyToLoad(false)
{
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle(tr("Импорт - ") + aTitle);

    CreateWidgets();
}

void Loader::closeEvent(QCloseEvent *aE)
{
    Sett::GetMA()->closeActiveSubWindow();
    aE->accept();
}

void Loader::keyPressEvent(QKeyEvent *aE) {
    if(aE->key() == Qt::Key_Escape)
        close();
}

void Loader::CreateWidgets()
{
    QHBoxLayout *ltHeader = new QHBoxLayout();
    ltHeader->addWidget(edtFileName = new QLineEdit());

    ltHeader->addWidget(btnChangeFile = new QPushButton(tr("Выбрать файл")));
    connect(btnChangeFile, SIGNAL(clicked()), this, SLOT(ChangeFile()));

    ltHeader->addWidget(btnImport = new QPushButton(tr("Импортировать данные")));
    connect(btnImport, SIGNAL(clicked()), this, SLOT(ImportFromFile()));

    ltHeader->addWidget(btnLoad = new QPushButton(tr("Загрузить в базу")));
    connect(btnLoad, SIGNAL(clicked()), this, SLOT(LoadToBase()));

    QHBoxLayout *ltBody = new QHBoxLayout();
    ltBody->addWidget(tblResult = new QTableWidget());
    tblResult->setSelectionBehavior(QAbstractItemView::SelectRows);

    QVBoxLayout *ltFooter = new QVBoxLayout();
    ltFooter->addWidget(edtMessages = new QTextEdit());
    edtMessages->setMaximumHeight(100);
    edtMessages->setReadOnly(true);

    QVBoxLayout *ltMain= new QVBoxLayout(this);
    ltMain->addLayout(ltHeader, 0);
    ltMain->addLayout(ltBody, 1);
    ltMain->addLayout(ltFooter, 0);
    setLayout(ltMain);
}

inline void InitTbl(QTableWidget *aTbl, const TblHeader &aH)
{   QStringList h;
    aTbl->setColumnCount(aH.size());
    for (unsigned int i = 0; i < aH.size(); ++i)
    {
        aTbl->setColumnWidth(i, aH[i].second);
        h << aH[i].first;
    }
    aTbl->setHorizontalHeaderLabels(h);
}

void Loader::BasicInitWidgets(const TblHeader &aTblH)
{
    InitTbl(tblResult, aTblH);
}

void Loader::ChangeFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Импортирование"), "", tr("Файлы csv (*.csv)"));
    if (!fileName.isEmpty()) edtFileName->setText(fileName);
}

void Loader::ImportFromFile()
{
    try
    {
        QList<QStringList> resList = parser.ParseFile(edtFileName->text(), QChar(';'), GetColCountConstraint());
        isReadyToLoad = Handle(resList);
    }
    catch (Error err)
    {
        QMessageBox::critical(Sett::GetMA(), Sett::GetErrMsgTitle(), err.msg());
        return;
    }
}

void Loader::EmptyTblResult()
{
    for (unsigned int i = 0; i < tblResult->rowCount(); ++i)
        for (unsigned int j = 0; j < tblResult->columnCount(); ++j)
            delete tblResult->item(i, j);
}

void Loader::LoadToBase()
{
    if (!isReadyToLoad)
    {
        QMessageBox::critical(Sett::GetMA(), Sett::GetErrMsgTitle(), tr("Данные не импортированы"));
        return;
    }

    int btn = QMessageBox::question(this,
        tr("Подтверждение загрузки"),
        tr("Вы действительно хотите загрузить импортированные данные?"),
            QMessageBox::Yes | QMessageBox::No);

    if (btn == QMessageBox::No) return;

    SpecLoadToBase();
}

/******************************* Class for loading reg nums *******************************/

LoaderRegNum::LoaderRegNum(QWidget *aParent):
    Loader(aParent, tr("Регистрационные номера"))
{
    InitWidgets();
    tblResult->hideColumn(0);
}

void LoaderRegNum::InitWidgets()
{
    TblHeader header;
    header
        << TblHeaderItem(tr("ID"), 50)
        << TblHeaderItem(tr("ФИ в файле"), 220)
        << TblHeaderItem(tr("ФИО в базе"), 220)
        << TblHeaderItem(tr("Рег. номер в файле"), 150)
        << TblHeaderItem(tr("Рег. номер в базе"), 150)
        << TblHeaderItem(tr(""), 20);
    BasicInitWidgets(header);
}

unsigned int LoaderRegNum::GetColCountConstraint() const
{
    return CSV_COL_COUNT;
}

QList<QRegExp> GetListRegExp(const QString &aFamily, const QString &aName)
{
    QList<QRegExp> res;
    if (aName.isEmpty() || aFamily.isEmpty()) return res;
    res
        << QRegExp("\\b" + aFamily + "\\b", Qt::CaseInsensitive)
        << QRegExp("\\b" + aFamily + "\\b\\W+" + aName.left(1) + ".*", Qt::CaseInsensitive)
        << QRegExp("\\b" + aFamily + "\\b\\W+" + aName + "\\b", Qt::CaseInsensitive);
    return res;
}

bool LoaderRegNum::Handle(const QList<QStringList> &aList)
{
    typedef QPair<QList<QRegExp>, QPair<QString, QString> > PairRXSportsman;
    typedef QMap<QString, RecSportsman> MapSportsman;

    QList<PairRXSportsman> listSearch;
    foreach (const QStringList &sportsman, aList)
    {
        QStringList::const_iterator it = sportsman.begin();
        QString family = *it;
        QString name = *++it;
        QString regNum = *++it;
        listSearch <<
            PairRXSportsman(
                GetListRegExp(family, name),
                QPair<QString, QString>(family + " " + name, regNum)
            );
    }

    MapSportsman mapSp;
    QSqlQuery query;
    edtMessages->clear();

    query.exec("select name, reg_number, id from sportsmen");
    while (query.next())
    {
        QString fio = query.record().value(0).toString().simplified();
        QString regNum = query.record().value(1).toString().simplified();
        int id = query.record().value(2).toInt();
        foreach (const PairRXSportsman &pRXSp, listSearch)
        {
            unsigned int index = 0;
            foreach (const QRegExp &rx, pRXSp.first)
            {
                if (rx.indexIn(fio) == -1) break;
                ++index;
            }
            if (index)
            {
                QString fioFile = pRXSp.second.first;
                MapSportsman::iterator it = mapSp.find(fioFile);
                if (it == mapSp.end() || (*it).rxIndex < index)
                {
                    mapSp[fioFile] = RecSportsman(id, fio, regNum, pRXSp.second.second, index);
                }
            }
        }
    }
    EmptyTblResult();
    tblResult->setRowCount(mapSp.size());
    unsigned int counter = 0;
    for (MapSportsman::const_iterator it = mapSp.begin(); it != mapSp.end(); ++it)
    {
        QTableWidgetItem* chbxItem, *regFileItem, *regDBItem, *fioFileItem, *fioDBItem;
        RecSportsman sp = it.value();

        tblResult->setItem(counter, eIdSp, new QTableWidgetItem(QString::number(sp.idSp)));
        tblResult->setItem(counter, eFioFile, fioFileItem = new QTableWidgetItem(it.key()));
        tblResult->setItem(counter, eFioDB, fioDBItem = new QTableWidgetItem(sp.fioDB));
        tblResult->setItem(counter, eRegFile, regFileItem = new QTableWidgetItem(sp.regFile));
        tblResult->setItem(counter, eRegDB, regDBItem = new QTableWidgetItem(sp.regDB));
        tblResult->setItem(counter, eSelRec, chbxItem = new QTableWidgetItem());

        chbxItem->setTextAlignment(Qt::AlignCenter);
        chbxItem->setFlags(chbxItem->flags() | Qt::ItemIsUserCheckable);

        Qt::ItemFlags itemFlag = Qt::ItemIsSelectable|Qt::ItemIsEnabled;
        fioFileItem->setFlags(itemFlag);
        fioDBItem->setFlags(itemFlag);
        regFileItem->setFlags(itemFlag);
        regDBItem->setFlags(itemFlag);

        if (sp.regFile == sp.regDB)
            chbxItem->setCheckState(Qt::Unchecked);
        else if (!sp.regDB.isEmpty() && sp.regFile != sp.regDB)
        {
            regFileItem->setTextColor(QColor(Qt::red));
            regDBItem->setTextColor(QColor(Qt::red));
            chbxItem->setCheckState(Qt::Unchecked);
        }
        else
        {
            fioFileItem->setTextColor(QColor(Qt::darkGreen));
            fioDBItem->setTextColor(QColor(Qt::darkGreen));
            chbxItem->setCheckState(Qt::Checked);
        }

        ++counter;
    }
    counter = 0;
    foreach (const PairRXSportsman &pRXSp, listSearch)
    {
        if (mapSp.contains(pRXSp.second.first)) continue;
        edtMessages->append(
            QString::number(++counter) + tr(". Спортсмен \"") + pRXSp.second.first + tr("\" в базе не найден"));
    }
    return !mapSp.isEmpty();
}

void LoaderRegNum::SpecLoadToBase()
{
    QSqlQuery query;
    unsigned int counter = 0;
    for (unsigned int i = 0; i < tblResult->rowCount(); ++i)
    {
        QTableWidgetItem *chbx = tblResult->item(i, eSelRec);
        if (chbx->checkState() == Qt::Unchecked) continue;

        QTableWidgetItem *regFileItem = tblResult->item(i, eRegFile);
        QTableWidgetItem *idSpItem = tblResult->item(i, eIdSp);
        QString str = "update sportsmen set reg_number = '" + regFileItem->text() +
            "' where id = " + idSpItem->text();
        counter += query.exec(str);

    }
    QMessageBox::information(
        Sett::GetMA(), tr("Сообщение"), tr("Записей изменено: ") + QString::number(counter));
}
