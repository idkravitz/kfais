#include "headers/xmlreports.h"
#include <QFileDialog>


QString ReportsMaker::PickName(ReportType rt)
{
    return QFileDialog::getSaveFileName(0,
                            QObject::tr("Сохранить отчёт в..."),
                            QObject::tr("report.xml"),
                            QObject::tr("XML files (*.xml)"));
}

void ReportsMaker::MakeReport(const QString &query, const ReportType type)
{
    QString filename = PickName(type);
    // 1. Run query, get data
    // 2. Form an xml pre output
    // 3. Look for xsl for this report type
    // 4. Apply XSLT
    // 5. Output a final xml output
}
