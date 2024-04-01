#include "src/CommonHelper.h"

#include "src/mainwindow.h"
#include <QAbstractTableModel>
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  // 加载QSS样式
  // CommonHelper::setStyle("style.qss");
  MainWindow   w;
  w.show();
  return a.exec();
}
