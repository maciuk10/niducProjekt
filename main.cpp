#include "vpsserwer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VPSSerwer w;
    w.show();

    return a.exec();
}
