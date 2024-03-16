#include "mianwidget.h"
#include "src/CommonHelper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 加载QSS样式
    CommonHelper::setStyle("style.qss");

    MianWidget w;
    w.show();
    return a.exec();
}
