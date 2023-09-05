#include "makereports.h"
#include "reportmaker.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    makeReports w;
    w.show(); 
    return a.exec();
}
