#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setSamples(4); // сглаживание
    QSurfaceFormat::setDefaultFormat(fmt);

    a.setApplicationName("BarterApp");
    a.setApplicationDisplayName("Бартерный Обмен — Общежитие");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("University Project");

    a.setStyle("Fusion");

    MainWindow w;
    w.show();
    return a.exec();
}
