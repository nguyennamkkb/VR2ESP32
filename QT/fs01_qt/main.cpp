#include "fs01_qt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fs01_qt w;
    w.show();

    return a.exec();
}
