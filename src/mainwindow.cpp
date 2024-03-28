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
// todo 书签 pdf 专注模式
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
  this->setGeometry(0, 0, 800, 600);  // 规范窗体大小
  gridLayout = new QGridLayout(this); // 主要布局

  gridLayout->setSpacing(0);          // 表示各个控件之间的上下间距
  gridLayout->setContentsMargins(0, 0, 0, 0);

  // 创建布局放按钮
  buttonlayout = new QGridLayout(); // 左侧一个垂直布局放按钮组
  buttonlayout->setContentsMargins(0, 0, 0, 0);
  buttonlayout->setSizeConstraint(QLayout::SetFixedSize);
  buttonlayout->setSpacing(0);

  mainWidget = new QStackedWidget(this); // 右侧一个stacked显示不同的界面

  // gridLayout->addLayout(buttonlayout, 0, 1);
  gridLayout->addWidget(mainWidget, 1, 1);
  // 创建table按钮，切换界面
  tablebtnGroup = new QButtonGroup(this);
  tablebtnGroup->setExclusive(true);
  newPage("课表");
  newPage("日程");
  newPage("今天");
  newPage("设置");

  tablebtnGroup->buttons().at(0)->setChecked(true);
  connect(tablebtnGroup, &QButtonGroup::idClicked, this, [&](int id) {
    mainWidget->setCurrentIndex(id); // 用按钮对应的id切换stackedwidget的页面
  });

  mainWidget->addWidget(new CourseScheduleWidget);
  mainWidget->addWidget(new taskandGoalWidget);
  mainWidget->addWidget(new TimeLineWidget);
}
#if defined(Q_OS_WIN)
#elif defined(Q_OS_ANDROID)
#endif
void MainWindow::resizeEvent(QResizeEvent* event) {
  if (nullptr != gridLayout) {
    int index = 0;
    if (this->geometry().width() < 500) {
      gridLayout->removeItem(buttonlayout);
      gridLayout->addLayout(buttonlayout, 2, 1); // 下方
      for (auto i : tablebtnGroup->buttons()) {
        buttonlayout->addWidget(i, 0, index++);  // 横着
      }
    } else if (this->geometry().width() > 500) {
      gridLayout->removeItem(buttonlayout);
      gridLayout->addLayout(buttonlayout, 1, 0); // 左侧
      for (auto i : tablebtnGroup->buttons()) {
        buttonlayout->addWidget(i, index++, 0);  // 竖着
      }                                          // todo需要一个弹簧
    }
  }
}
void MainWindow::newPage(const QString& name) {
  QSize        buttonSize(100, 25);
  static int   index      = 0;
  QPushButton* pushbutton = new QPushButton(name);
  pushbutton->setMinimumSize(buttonSize);
  pushbutton->setCheckable(true); // 设置按钮可以按下不抬起
  buttonlayout->addWidget(pushbutton, 0, index);
  tablebtnGroup->addButton(pushbutton, index++);
}
void MainWindow::on_test_clicked() {
  qDebug() << "yes";
}
