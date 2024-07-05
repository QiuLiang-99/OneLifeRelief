#include "CommonHelper.h"

#include "model/task/taskdata.h"
#include "wigdet/mainwindow/mainwindow.h"
#include <QApplication>

#include <cstdint>
#include <iostream>
#include <qlist.h>
#include <qlogging.h>

// todo 整个软件只能打开一次，不能多次打开
int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  // 加载QSS样式
  // CommonHelper::setStyle("style.qss");
  MainWindow   w;
  w.show();
  return a.exec();
}
