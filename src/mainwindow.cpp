#include "mainwindow.h"
#include <qforeach.h>
#include <qlist.h>
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  setupUI();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
  this->setGeometry(0, 0, 800, 600);  // 规范窗体大小

  gridLayout = new QGridLayout(this); // 主要布局
  gridLayout->setSpacing(0);          // 表示各个控件之间的上下间距
  QMargins blanket;
  gridLayout->setContentsMargins(blanket);

#if defined(Q_OS_WIN)
  // 创建布局放按钮
  buttonlayout = new QVBoxLayout(this);
  buttonlayout->setSizeConstraint(QLayout::SetFixedSize);
  buttonlayout->setSpacing(0);

  mainWidget = new QStackedWidget(this);

  gridLayout->addLayout(buttonlayout, 0, 1);
  gridLayout->addWidget(mainWidget, 0, 2);
  // 创建table按钮
  QButtonGroup* tablebtnGroup = new QButtonGroup(this);
  tablebtnGroup->setExclusive(true);
  QList<QPushButton*> tablebtn = {new QPushButton("kaise"), new QPushButton,
                                  new QPushButton, new QPushButton};
  QSize               buttonSize(100, 25);
  int                 index = 0;
  for (auto pushbutton : tablebtn) {
    pushbutton->setMinimumSize(buttonSize);
    buttonlayout->addWidget(pushbutton);
    tablebtnGroup->addButton(pushbutton, index++);
    // pushbutton->setStyleSheet("pushbutton{margin:0}");
  }
  connect(tablebtnGroup, &QButtonGroup::idClicked, this, [&](int id) {
    mainWidget->setCurrentIndex(id); // 用按钮对应的id切换stackedwidget的页面
  });

  QLabel* l = new QLabel("Hello World"); // 新建Label
  buttonlayout->addWidget(l);

  QWidget*            page_1       = new QWidget;
  QHBoxLayout*        page_1H      = new QHBoxLayout(page_1);
  CourseScheduleView* ScheduleView = new CourseScheduleView(page_1);
  page_1H->addWidget(ScheduleView);
  mainWidget->addWidget(page_1);

#elif defined(Q_OS_ANDROID)
  QLabel* l = new QLabel("Hello Android");
#endif
}
