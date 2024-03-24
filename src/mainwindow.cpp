#include "mainwindow.h"
#include <QLabel>
#include <qboxlayout.h>
#include <qframe.h>
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  QGridLayout* gridLayout = new QGridLayout(this);

  gridLayout->setSpacing(0); // 表示各个控件之间的上下间距
#if defined(Q_OS_WIN)

  QVBoxLayout* buttonlayout = new QVBoxLayout;
  buttonlayout->setSpacing(0);
  gridLayout->addLayout(buttonlayout, 0, 1);
  QPushButton* pushbutton = new QPushButton;
  buttonlayout->addWidget(pushbutton);
  QLabel* l = new QLabel("Hello World"); // 新建Label
  buttonlayout->addWidget(l);

#elif defined(Q_OS_ANDROID)
  QLabel* l = new QLabel("Hello Android");
#endif
}

MainWindow::~MainWindow() {
}
