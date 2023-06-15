#include "qwight.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Qwight w;
    w.show();

    return a.exec();
}
