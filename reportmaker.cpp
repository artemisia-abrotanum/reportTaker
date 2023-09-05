#include "reportmaker.h"
#include <QHeaderView>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>


ReportMaker::ReportMaker(QString head):
    html(QString())
  , end (false)
{
    renewDoc(head);
}

void ReportMaker::addText(const QStringList& text, const QString& header, int level)
{
    if (!header.isEmpty()){
        html.append(QString("<h%1 align: center;>").arg(level));
        html.append(header);
        html.append(QString("</h%1>").arg(level));
    }
    for(auto p : text){
        html.append("<p>");
        html.append(p);
        html.append("</p>");
    }
}

void ReportMaker::addImage(const QString &imgName, /*QString vspace,*/ const QString& header, int level, int size)
{
    QString imgstr;
    imgstr.append(QString("<h%1>").arg(level));
    imgstr.append(header);
    imgstr.append(QString("</h%1><p>").arg(level));
    imgstr.append(" <a href=\"");
    imgstr.append(imgName);
    imgstr.append(QString("\"><center>"
                  "<img src=\"%1\"").arg(imgName));
    //TODO: vspace
    //    if (!vspace.isEmpty()) {
    //        imgstr.append("vspace=\\");
    //        imgstr.append(vspace);
    //        imgstr.append("px\\ \" ");
    //    }
    imgstr.append(QString("width=\"%1\" /></center></a></p>").arg(size)); //TODO: "width=\"500%\" dontwork?
    html.append(imgstr);
}

void ReportMaker::renewDoc(const QString& header)
{
    html.clear();
    html.append(QString("<html lang=\\en\\>"
                        "<head><meta http-equiv=\\content-type\\content=\\text/html; charset=utf-8\\>"
                        "<title> %1 </title>"
                        "<link rel='stylesheet' href='/styles.css' type='text/css>"
                        "<style type='text/css'>"
                        "</head>").arg(header));
    //________________________body
    html.append(QString("<footer>"
                        "<p size=\"10px\" align=\"right\"><small>%1</small></p>"
                        "</footer>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy,hh:mm")));

    //________________________caption
    html.append(QString("<h1  align= center> %1</h1>").arg(header));
    end = false;
}

bool ReportMaker::save(const QString& reportName, const QString& reportPath, const QPageLayout::Orientation& orient)
{
    checkEnd();
    QPrinter printer(QPrinter::HighResolution);
    printer.setColorMode(QPrinter::Color);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setPageOrientation(orient);
    //    setPaperSize(QPrinter::A4);
    printer.setPageMargins(QMarginsF(0, 0, 0, 2));//_________________________bottom=2mm because we need to print number of pages

    QString name=reportPath;
    name.append(QString("/%1.pdf").arg(reportName));
    printer.setOutputFileName(name);

    QTextDocument td;
    td.setHtml(html);
    td.print(&printer);
    return true;
}

bool ReportMaker::print()
{
    checkEnd();
    QPrinter printer;
    QPrintDialog qp (&printer);
    if (qp.exec() == QDialog::Accepted) {
        QTextDocument td;
        td.setHtml(html);
        td.print(dynamic_cast<QPagedPaintDevice*>(&printer)); //TODO: Invalid parameter passed to C runtime function.
        return true;
    }
    return false;
}

void ReportMaker::checkEnd()
{
    if(!end){
        html.append("</body> </html>");
        end = true;
    }
}

