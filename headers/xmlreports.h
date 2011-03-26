#ifndef XMLREPORTS_H
#define XMLREPORTS_H

#include<QtXml>
#include<QtSql>

enum ReportType {
    UniversalReport,
    WeightProtocol,
    PulkaReport,
    CertificationProtocol,
    CompetitionsResultsProtocol
};

class ReportsMaker {
    QString PickName(ReportType rt);
public:
    void MakeReport(const QString &query, const ReportType type=UniversalReport);
};


#endif // XMLREPORTS_H

