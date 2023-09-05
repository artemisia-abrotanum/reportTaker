#include "makereports.h"
#include "ui_makereports.h"

#include <QFile>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QSizePolicy>
#include <QDebug>
#include <QDir>

makeReports::makeReports(QWidget *parent)
    : QMainWindow(parent)
    , report(new ReportMaker("rep"))
    , ui(new Ui::makeReports)
{
    ui->setupUi(this);
}

makeReports::~makeReports()
{
    delete report;
    delete ui;
}


void makeReports::on_tableBTN_clicked()
{
    QList<QString> data = ui->tableDataLN->toPlainText().split(";");
    QStringList hdr{ui->tablHeadLN->text().split(";")};
    report->addTable(data, hdr, "table", 3, nullptr);
}


void makeReports::on_textBTN_clicked()
{
    report->addText(ui->textLN->text().split("/n"), "");
}


void makeReports::on_pushButton_2_clicked()
{
    qDebug()<<"save"<<report->save("mytestrep", QDir::currentPath());
}


void makeReports::on_imgBTN_clicked()
{
    report->addImage(ui->imgLN->text(), "");
}


void makeReports::on_pushButton_clicked()
{
    qDebug()<<"print"<<report->print();
}


void makeReports::on_headBTN_clicked()
{
    report->renewDoc(ui->headLN->text());
}


void makeReports::on_pushButton_3_clicked()
{
    QList<int> dat;
    for (int i=0; i< 100; i++) dat.append(i);
    QList<QString> hdr {"fist", "second", "last"};
    report->addTable(dat, hdr, "table", 3, nullptr);
    report->addImage("cat.png", "my test image");
    report->addText(QStringList{"Отражение (рефлексия; холоним интроспекции, англ. reflection) — процесс, во время которого программа может отслеживать и модифицировать собственную структуру и поведение во время выполнения.",
                                "Парадигма программирования, положенная в основу отражения, является одной из форм метапрограммирования[1] и называется рефлексивным программированием.",
                                "Понятие рефлексии в языках программирования введено Брайаном Смитом (Brian Cantwell Smith) в докторской диссертации 1982 года[2][3] наряду с понятием метациркулярного вычислителя (англ. Meta-circular evaluator) как компонента 3-Lisp."},
                    "new text");
}

