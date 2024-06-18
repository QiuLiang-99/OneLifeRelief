#include "src/CommonHelper.h"
#include "src/mainwindow.h"
#include "src/model/task/taskdata.h"
#include "src/module/sqlite/snowflake/snowflake.h"
#include <QApplication>
#include <QTableWidget> // Add this line to import the QTableWidget class
#include <cstdint>
#include <qlist.h>
#include <qlogging.h>
// todo 整个软件只能打开一次，不能多次打开
int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  // 加载QSS样式
  // CommonHelper::setStyle("style.qss");
  qDebug() << "run!";
  MainWindow w;
  w.show();
  return a.exec();
}
