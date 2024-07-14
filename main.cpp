#include "sqlite/taskdao.h"
#include "utils/commonhelper.h"

#include "wigdet/mainwindow/mainwindow.h"
#include <QApplication>
// todo 启动参数
// todo 整个软件只能打开一次，不能多次打开
int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  // 加载QSS样式
  // CommonHelper::setStyle("style.qss");
  TaskDAO      dao;
  MainWindow   w;
  w.show();
  return a.exec();
}
