#ifndef REPORTMAKER_H
#define REPORTMAKER_H
#include <QStringList>
#include <QList>
#include <QPrinter>
#include <QTextDocument>
#include <QDateTime>


class ReportMaker
{
public:
    ReportMaker(QString head="");

    template<typename t>
    void addTable(QList<t>& data, QStringList& tablehead, const QString& head="", int nColumn = 1,       // nColumn: part of list (column on list
                  const QMap<int, QString>* color=nullptr)
    {
        int cell = data.size();
        int nColumninReport = nColumn>0? nColumn : 1;
        int lines = tablehead.size()* nColumninReport;
        int nLines = (cell%lines) ? (cell/lines)+1 : (cell/lines);

        html.append(QString("<table table-layout: auto; width = \"100%\"; border=\"1\"; style=\"border-collapse:collapse\";> ")); //


        html.append(QString("<CAPTION>%1</CAPTION>").arg(head));//________________________caption
        html.append("<thead> <tr>");
        for(int hd=0; hd < nColumninReport; hd++){

            for (auto headcolmn : tablehead) { //_____________________________________________________________________________columns header
                html.append(QString("<th> %1</th>").arg(headcolmn));
            }
        }
        html.append("</tr></thead><tbody>");

        int n=0;
        for(int i=0; i <nLines; i++){
            html.append(QString ("<tr > "));
            for (int j=0; j < lines && n < cell; j++, ++n){
                html.append (QString("<td align= center>%1 </td>").arg(data[n]));
                // TODO: color
                //                if(color != nullptr) html.append (QString("<td align= center; >").arg(color->value(n)));
                //                else html.append ("<td align= center>");

                //                html.append(QString ("<a href= '%1'>").arg(address.at(0)));
                //                html.append(QString (" %1 </a></td><td text-align= center;").arg(statusV));    link
                //            html.append ("<td empty-cells: hide; > </td>");
            }
            html.append("</tr>");
        }
        html.append("</tbody> </table>");//_____________________________________________________________________end of table
    }
    //"color": (QString - .. ), (QString - color (like #000000))

    void addText(const QStringList& text, const QString &header="", int level=2);         //<h2>-<h6>
    void addImage(const QString& imgName,
                  const QString &header="", int level=2, int size = 500);                          //vspace: only number, without "px"
    void renewDoc(const QString &header);                                          //only <h1>
    //    TODO: void addTableWithReff();
    //    TODO: <ol>

    bool save(const QString &reportName, const QString &reportPath = "", const QPageLayout::Orientation &orient = QPageLayout::Portrait);
    bool print();


private:
    QString html;
    bool end;
    void checkEnd();

};
#endif // REPORTMAKER_H
