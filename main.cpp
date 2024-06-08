#include "src/mainwindow.h"
#include "src/model/task/taskdata.h"
#include <QApplication>
#include <QTableWidget> // Add this line to import the QTableWidget class

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  // 加载QSS样式
  // CommonHelper::setStyle("style.qss");
  qDebug() << "run!";
  MainWindow   w;
  QTableWidget e; // Replace 'qtablewidget' with 'QTableWidget'
  TaskData     t;
  w.show();
  return a.exec();
}
