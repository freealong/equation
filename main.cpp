#include <QApplication>
#include "gui/gui.h"
#include "gui/MainWidget.h"
#include "core/test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gui w;
    w.show();
    MainWidget cropWidget;
    QObject::connect(&w, SIGNAL(beginScreenshot()), &cropWidget, SLOT(DoScreenshot()));
    QObject::connect(&cropWidget, SIGNAL(finishCrop(const QPixmap&)), &w, SLOT(finishScreenshot(const QPixmap&)));

    test();

    return a.exec();
}
