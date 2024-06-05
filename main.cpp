#include "src/mainwindow.h"
#include <QApplication>
#include <QTableWidget> // Add this line to import the QTableWidget class

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  // 加载QSS样式
  // CommonHelper::setStyle("style.qss");
  qDebug() << "run!";
  MainWindow   w;
  QTableWidget e; // Replace 'qtablewidget' with 'QTableWidget'
  w.show();
  return a.exec();
}
