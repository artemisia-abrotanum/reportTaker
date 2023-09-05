#ifndef MAKEREPORTS_H
#define MAKEREPORTS_H

#include "reportmaker.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class makeReports; }
QT_END_NAMESPACE

class makeReports : public QMainWindow
{
    Q_OBJECT

public:
    makeReports(QWidget *parent = nullptr);
    ~makeReports();
    ReportMaker* report;

private slots:

    void on_tableBTN_clicked();

    void on_textBTN_clicked();

    void on_pushButton_2_clicked();

    void on_imgBTN_clicked();

    void on_pushButton_clicked();

    void on_headBTN_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::makeReports *ui;
};


#endif // MAKEREPORTS_H
