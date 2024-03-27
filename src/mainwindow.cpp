#include "mainwindow.h"
#include "src/CourseScheduleView.h"
#include "src/taskandGoalView.h"
#include "src/timeline.h"
#include <qcontainerfwd.h>
#include <qforeach.h>
#include <qlist.h>
#include <qpushbutton.h>
// todo 窗口随着大小改变而改变控件QResizeEvent
//  todo 提前时间累计
// todo任务提醒
// todo 商品价格计算 质保
// todo 收入支出前后 钱包
// todo 技能学习 md写法
// todo 信用卡还款 资金
// todo 书签 pdf
// todo 所有的map都可以随意改名字ortheyaretemplatejustchose one tocreate
// todo 生存map之后管理，可以看到进度条，每个project有哪些完成和没完成
// todo treehead Title Prioritized backlog 表头动item不动
/*Status
    Title
    Assignees
        Size
            Estimate
                Linked pull requests
                    Iteration
                        Start date
                            End date*/
// todo Status board 拖拽选项卡
/*name inside outside*/
/*Backlog #DAFBE1 #1F883D

Estimate:0
 Ready #DDF4FF #0969DA
Estimate:0
In progress #FFF8C5 #9A6700

Estimate:0
In review #FBEFFF #8250DF
Estimate:0
Done #FFF1E5 #BC4C00
0 Estimate:0*/
// todo Roadmap
/*March 2024
8
9
10
11
12
13
14*/
MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  setupUI();
}

MainWindow::~MainWindow() {
}
void MainWindow::setupUI() {
  newWidget();
  QStringList pageName;
  auto        e = pageName.cbegin();
  pageName << "课表"
           << "日程"
           << "今天"
           << "设置";
  int index = 0;
  newPage(new CourseScheduleWidget, "课表", index++);
  newPage(new taskandGoalWidget, "日程", index++);
  newPage(new TimeLineWidget, "今天", index++);
  newPage(new CourseScheduleView, "课表", index++);

  tablebtnGroup->button(0)->setChecked(true);
  connect(tablebtnGroup, &QButtonGroup::idClicked, this, [&](int id) {
    mainWidget->setCurrentIndex(id); // 用按钮对应的id切换stackedwidget的页面
  });
#if defined(Q_OS_WIN)
#elif defined(Q_OS_ANDROID)
#endif
}
void MainWindow::newPage(QWidget* page, const QString& name, const int& id) {
  QPushButton* btn = new QPushButton(name);
  QSize        buttonSize(100, 25);
  btn->setMinimumSize(buttonSize);
  btn->setCheckable(true); // 设置按钮可以按下不抬起
  tablebtnGroup->addButton(btn, id);
  mainWidget->addWidget(page);
}
void MainWindow::resizeEvent(QResizeEvent* event) {
  if (nullptr != gridLayout) {
    int index = 0;
    if (this->geometry().width() < 500) {
      gridLayout->removeItem(buttonlayout);
      gridLayout->addLayout(buttonlayout, 1, 0); // 放到左侧，竖着
      for (auto i : tablebtnGroup->buttons()) {
        buttonlayout->addWidget(i, index++, 0);
      }
      QSpacerItem* Vsparcer = // 添加弹簧防止太多空隙
          new QSpacerItem(160, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
      buttonlayout->addItem(Vsparcer, 10, 0);
    } else if (this->geometry().width() > 500) {
      gridLayout->removeItem(buttonlayout);
      gridLayout->addLayout(buttonlayout, 2, 1); // 放到下方，横着
      for (auto i : tablebtnGroup->buttons()) {
        buttonlayout->addWidget(i, 0, index++);
      }
      // bug 窗口不贴合底部
    }
  }
}

void MainWindow::newWidget() {
  this->setGeometry(0, 0, 800, 600);  // 规范窗体大小
  gridLayout = new QGridLayout(this); // 主要布局
  gridLayout->setSpacing(0);          // 表示各个控件之间的上下间距
  gridLayout->setContentsMargins(0, 0, 0, 0);
  buttonlayout = new QGridLayout();   // 左侧一个垂直布局放按钮组
  buttonlayout->setContentsMargins(0, 0, 0, 0);
  buttonlayout->setSizeConstraint(QLayout::SetFixedSize);
  buttonlayout->setSpacing(0);
  mainWidget = new QStackedWidget(this); // 用stacked显示不同的界面
  gridLayout->addWidget(mainWidget, 1, 1);
  tablebtnGroup = new QButtonGroup(this);
  tablebtnGroup->setExclusive(true);
}
void MainWindow::on_test_clicked() {
  qDebug() << "yes";
}
