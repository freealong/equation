#include <QApplication>
#include "gui/gui.h"
#include "core/test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui w;
    w.show();

    test();

    return a.exec();
}
