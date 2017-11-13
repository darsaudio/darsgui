#include "mainwindow.h"
#include <stdlib.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int ret = 0;

    ret = system("pacmd list-modules | grep module-dbus-protocol 1>/dev/null 2>&1");
    if (ret) {
        system("pacmd load-module module-dbus-protocol 1>/dev/null 2>&1");
    }

    ret = system("pacmd list-modules | grep module-dars-sink 1>/dev/null 2>&1");
    if (ret) {
        system("pacmd load-module module-dars-sink 1>/dev/null 2>&1");
    }

    w.show();

    return a.exec();
}
