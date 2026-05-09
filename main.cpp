#include <QApplication>
#include "mainwindow.h"
#include "services/dataservice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Course Helper");
    a.setApplicationDisplayName("Course Helper");

    DataService::ensureDataFiles();

    MainWindow w;
    w.setWindowTitle("Course Helper");
    w.show();
    return a.exec();
}