#include "welcome.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Welcome w;
    w.setFixedSize(2000, 1200);
    w.show();

    return a.exec();
}
