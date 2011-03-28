#include "headers/xmlreports.h"
#include <QFileDialog>
#include <QMessageBox>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

#define DEBUG

QString ReportsMaker::PickName(ReportType rt)
{
    return QFileDialog::getSaveFileName(0,
                            QObject::tr("Сохранить отчёт в..."),
                            QObject::tr("report.xml"),
                            QObject::tr("XML files (*.xml)"));
}

void ReportsMaker::CreateRawReport(QSqlQuery &query, QFile &file)
{
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("root");
    while(query.next())
    {
        xml.writeStartElement("row");
        for(int i = 0; i < query.record().count(); ++i)
        {
            xml.writeStartElement("column");
            xml.writeCharacters(query.value(i).value<QString>());
            xml.writeEndElement();
        }
        xml.writeEndElement();
    }
    xml.writeEndElement();
    xml.writeEndDocument();
}

QString ReportsMaker::GetPathToStylesheet(const ReportType)
{
    return "templates/report.xsl";
}

void ReportsMaker::MakeReport(const QString &queryString, const ReportType type)
{
    QTemporaryFile inputxml("report");
    inputxml.setAutoRemove(false);
    inputxml.open();

    QSqlQuery query(queryString);
    CreateRawReport(query, inputxml);
    QString inputname = inputxml.fileName();
    inputxml.close();

    QString xsltname = GetPathToStylesheet(type);

    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;
    xmlDocPtr inpXmlPtr = xmlParseFile(inputname.toAscii().constData());
    xsltStylesheetPtr inpXsltPtr = xsltParseStylesheetFile((const xmlChar*)xsltname.toAscii().constData());
    const char **params = {'\0'};
    xmlDocPtr result = xsltApplyStylesheet(inpXsltPtr, inpXmlPtr, params);
    xsltSaveResultToFilename("report.xml", result, inpXsltPtr, 0);

    xsltFreeStylesheet(inpXsltPtr);
    xmlFreeDoc(inpXmlPtr);
    xmlFreeDoc(result);
    xsltCleanupGlobals();
    xmlCleanupParser();

}
