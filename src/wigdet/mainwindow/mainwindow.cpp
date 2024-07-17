#include "mainwindow.h"

#include "src/wigdet/mainwindow/functionwindow/taskandgoal/taskandgoal.h"
#include "src/wigdet/mainwindow/functionwindow/timeline/timeline.h"

// #include "src/module/olrmainwindow/olrmainwindow.h"
#include "src/wigdet/mainwindow/functionwindow/courseschedule/courseschedulewidget.h"
// #include "src/wigdet/mainwindow/functionwindow/setting/setting.h"
#include "src/wigdet/mainwindow//olrmainwindow.h"
#include <qsize.h>
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
// todo 还需要一个日历视图的页面
// todo 自主添加表头，自动调换
// todo 日历，每天睡觉时间，推算，定时，闹钟
// todo 番茄钟，专注
// todo Status board 拖拽选项卡
// todo通过创建的时间的标签查找
// todo 睡眠 助眠，听歌，更新
// todo An alternative to putting the plugins in the plugins subdirectory is to
// add a custom search path when you start your application using
// QCoreApplication::addLibraryPath() or QCoreApplication::setLibraryPaths().
// todo Roadmap
/*
March 2024
8
9
10
11
12
13
14
*/

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) { setupUI(); }
void MainWindow::setupUI() {
#if defined(Q_OS_WIN)
  int   windowWidth  = 800;
  int   windowHeight = 600;
  QSize size         = QSize(windowWidth, windowHeight);
  setFixedSize(size);
#elif defined(Q_OS_ANDROID)
  QScreen* screen         = QGuiApplication::primaryScreen();
  QRect    screenGeometry = screen->geometry();
  int      height         = screenGeometry.height();
  int      width          = screenGeometry.width();
  QSize    size           = QSize(width, height);
  setFixedSize(size);
#endif

  gridLayout = new QGridLayout(this); // 主要布局

  gridLayout->setSpacing(0);          // 表示各个控件之间的上下间距
  gridLayout->setContentsMargins(0, 0, 0, 0);

  // 创建布局放按钮

  btnHLayout = new QHBoxLayout();
  btnHLayout->setContentsMargins(0, 0, 0, 0);
  btnHLayout->setSizeConstraint(QLayout::SetFixedSize);
  btnHLayout->setSpacing(0);

  btnVLayout = new QVBoxLayout();
  btnVLayout->setContentsMargins(0, 0, 0, 0);
  btnVLayout->setSizeConstraint(QLayout::SetFixedSize);
  btnVLayout->setSpacing(0);

  mainWidget = new QStackedLayout; // 右侧一个stacked显示不同的界面

  // gridLayout->addLayout(buttonlayout, 0, 1);
  gridLayout->addLayout(mainWidget, 1, 1);
  // 创建table按钮，切换界面
  tablebtnGroup = new QButtonGroup(this);
  tablebtnGroup->setExclusive(true);
  appendNewButton("课表");
  appendNewButton("日程");
  appendNewButton("今天");
  appendNewButton("设置");

  btnVLayout->insertStretch(-1); // 相当于在底部添加了一个弹簧

  tablebtnGroup->buttons().at(0)->setChecked(true);
  connect(tablebtnGroup, &QButtonGroup::idClicked, this, [&](int id) {
    mainWidget->setCurrentIndex(id); // 用按钮对应的id切换stackedwidget的页面
  });

  mainWidget->addWidget(new CourseScheduleWidget);
  mainWidget->addWidget(new taskandGoalWidget);
  mainWidget->addWidget(new TimeLineWidget);
  // mainWidget->addWidget(new OLRMainWindow);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  Q_UNUSED(event);
  if (nullptr != gridLayout) {
    int       index     = 0;
    int       width     = this->geometry().width();
    const int threshold = 500;
    if (width < threshold) {
      gridLayout->removeItem(btnVLayout);
      gridLayout->addLayout(btnHLayout, 2, 1); // 下方横着

    } else {
      gridLayout->removeItem(btnHLayout);
      gridLayout->addLayout(btnVLayout, 1, 0); // 左侧竖着
                                               // todo需要一个弹簧
    }
  }
}
void MainWindow::appendNewButton(const QString& name) {
  QSize        buttonSize(100, 25);
  static int   index      = 0;
  QPushButton* pushbutton = new QPushButton(name);
  pushbutton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  pushbutton->setMinimumSize(0, 0); // 设置最小尺寸可以无限缩小
  // pushbutton->setFixedSize(100, 25);
  pushbutton->setMaximumSize(buttonSize); // 设置最大尺寸为默认尺寸

  pushbutton->setCheckable(true);         // 设置按钮可以按下不抬起
  btnHLayout->addWidget(pushbutton);
  btnVLayout->addWidget(pushbutton);

  tablebtnGroup->addButton(pushbutton, index++);
}
void MainWindow::on_test_clicked() { qDebug() << "yes"; }
