#include "mainwindow.h"
#include "src/CourseScheduleView.h"
#include "src/taskandGoalView.h"
#include "src/timeline.h"
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
  gridLayout->setContentsMargins(0, 0, 0, 0);
#if defined(Q_OS_WIN)
  // 创建布局放按钮
  buttonlayout = new QVBoxLayout(); // 左侧一个垂直布局放按钮组
  buttonlayout->setContentsMargins(0, 0, 0, 0);
  buttonlayout->setSizeConstraint(QLayout::SetFixedSize);
  buttonlayout->setSpacing(0);

  mainWidget = new QStackedWidget(this); // 右侧一个stacked显示不同的界面

  gridLayout->addLayout(buttonlayout, 0, 1);
  gridLayout->addWidget(mainWidget, 0, 2);
  // 创建table按钮，切换界面
  QButtonGroup* tablebtnGroup = new QButtonGroup(this);
  tablebtnGroup->setExclusive(true);
  QList<QPushButton*> tablebtn = {
      new QPushButton("课表"), new QPushButton("日程"), new QPushButton("今天"),
      new QPushButton("设置")};
  QSize buttonSize(100, 25);
  int   index = 0;
  for (auto pushbutton : tablebtn) {
    pushbutton->setMinimumSize(buttonSize);
    pushbutton->setCheckable(true); // 设置按钮可以按下不抬起
    buttonlayout->addWidget(pushbutton);
    tablebtnGroup->addButton(pushbutton, index++);
    // pushbutton->setStyleSheet("pushbutton{margin:0}");
  }
  tablebtn.at(0)->setChecked(true);
  connect(tablebtnGroup, &QButtonGroup::idClicked, this, [&](int id) {
    mainWidget->setCurrentIndex(id); // 用按钮对应的id切换stackedwidget的页面
  });
  // new一个高可以拉伸，宽度固定的弹簧在layout里直接additem(sparcer_item)即可
  QSpacerItem* VerticalSparcer =
      new QSpacerItem(0, 160, QSizePolicy::Fixed, QSizePolicy::Expanding);
  buttonlayout->addItem(VerticalSparcer);
  // todo 把每一个page写成一个函数
  QWidget*     page_1  = new QWidget;
  QHBoxLayout* page_1H = new QHBoxLayout(page_1);
  page_1H->setSpacing(0); // 表示各个控件之间的上下间距
  page_1H->setContentsMargins(0, 0, 0, 0);
  CourseScheduleView* ScheduleView = new CourseScheduleView(page_1);
  page_1H->addWidget(ScheduleView);
  mainWidget->addWidget(page_1);

  QWidget*         page_2   = new QWidget;
  QHBoxLayout*     page_2H  = new QHBoxLayout(page_2);
  taskandGoalView* taskView = new taskandGoalView;
  page_2H->setSpacing(0); // 表示各个控件之间的上下间距
  page_2H->setContentsMargins(0, 0, 0, 0);
  page_2H->addWidget(taskView);
  mainWidget->addWidget(page_2);

  QWidget*     page_3  = new QWidget;
  QHBoxLayout* page_3H = new QHBoxLayout(page_3);
  // taskandGoalView* taskView = new taskandGoalView;
  QPushButton* test    = new QPushButton(page_3);
  page_3H->setSpacing(0); // 表示各个控件之间的上下间距
  page_3H->setContentsMargins(0, 0, 0, 0);
  page_3H->addWidget(test);
  mainWidget->addWidget(page_3);
  Timeline* timeLine = new Timeline(this);
  page_3H->addWidget(timeLine);
  connect(test, &QPushButton::clicked, this, &MainWindow::on_test_clicked);

#elif defined(Q_OS_ANDROID)
  QLabel* l    = new QLabel("Hello Android");
  // 创建布局放按钮
  buttonlayout = new QVBoxLayout(); // 左侧一个垂直布局放按钮组
  buttonlayout->setContentsMargins(0, 0, 0, 0);
  buttonlayout->setSizeConstraint(QLayout::SetFixedSize);
  buttonlayout->setSpacing(0);

  mainWidget = new QStackedWidget(this); // 右侧一个stacked显示不同的界面

  gridLayout->addLayout(buttonlayout, 0, 1);
  gridLayout->addWidget(mainWidget, 0, 2);
  // 创建table按钮，切换界面
  QButtonGroup* tablebtnGroup = new QButtonGroup(this);
  tablebtnGroup->setExclusive(true);
  QList<QPushButton*> tablebtn = {
      new QPushButton("课表"), new QPushButton("日程"), new QPushButton("今天"),
      new QPushButton("设置")};
  QSize buttonSize(100, 25);
  int   index = 0;
  for (auto pushbutton : tablebtn) {
    pushbutton->setMinimumSize(buttonSize);
    pushbutton->setCheckable(true); // 设置按钮可以按下不抬起
    buttonlayout->addWidget(pushbutton);
    tablebtnGroup->addButton(pushbutton, index++);
    // pushbutton->setStyleSheet("pushbutton{margin:0}");
  }
  tablebtn.at(0)->setChecked(true);
  connect(tablebtnGroup, &QButtonGroup::idClicked, this, [&](int id) {
    mainWidget->setCurrentIndex(id); // 用按钮对应的id切换stackedwidget的页面
  });
  // new一个高可以拉伸，宽度固定的弹簧在layout里直接additem(sparcer_item)即可
  QSpacerItem* VerticalSparcer =
      new QSpacerItem(0, 160, QSizePolicy::Fixed, QSizePolicy::Expanding);
  buttonlayout->addItem(VerticalSparcer);
  // todo 把每一个page写成一个函数
  QWidget*     page_1  = new QWidget;
  QHBoxLayout* page_1H = new QHBoxLayout(page_1);
  page_1H->setSpacing(0); // 表示各个控件之间的上下间距
  page_1H->setContentsMargins(0, 0, 0, 0);
  CourseScheduleView* ScheduleView = new CourseScheduleView(page_1);
  page_1H->addWidget(ScheduleView);
  mainWidget->addWidget(page_1);
#endif
}

void MainWindow::on_test_clicked() {
  qDebug() << "yes";
}
