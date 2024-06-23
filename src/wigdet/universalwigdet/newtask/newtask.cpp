#include "newtask.h"
#include "src/model/task/taskdata.h"
#include "src/sqlite/snowflake/snowflake.h"
#include "src/sqlite/taskdb.h"
#include <qdatetime.h>

// todo 几小时 几天 后
// enter 快捷键
newTaskWidget::newTaskWidget(QWidget* parent) : QDialog(parent) {
  setWindowModality(Qt::WindowModal); // 模态窗口 无法点击其他窗口
  setWindowTitle("新建任务");
  mainLayout   = new QVBoxLayout(this);

  taskNameEdit = new QLineEdit(this);
  taskNameEdit->setPlaceholderText("任务名称");
  mainLayout->addWidget(taskNameEdit);

  descriptionEdit = new QTextEdit(this);
  descriptionEdit->setPlaceholderText("描述");
  mainLayout->addWidget(descriptionEdit);

  buttonLayout = new QHBoxLayout();

  todayButton  = new QPushButton("今天", this);
  buttonLayout->addWidget(todayButton);
  calendarWindow = new CalendarWindow(this);
  priorityButton = new QPushButton("优先级", this);
  buttonLayout->addWidget(priorityButton);

  remindButton = new QPushButton("提醒", this);
  buttonLayout->addWidget(remindButton);

  upgradeButton = new QPushButton("升级", this);
  buttonLayout->addWidget(upgradeButton);

  moreButton = new QPushButton("...", this);
  buttonLayout->addWidget(moreButton);

  mainLayout->addLayout(buttonLayout);

  inboxLayout   = new QHBoxLayout();
  inboxLabel    = new QLabel("收件箱", this);
  inboxComboBox = new QComboBox(this);
  inboxComboBox->addItem("收件箱");
  inboxLayout->addWidget(inboxLabel);
  inboxLayout->addWidget(inboxComboBox);
  mainLayout->addLayout(inboxLayout);

  actionLayout = new QHBoxLayout();
  cancelButton = new QPushButton("取消", this);
  addButton    = new QPushButton("添加任务", this);
  addButton->setStyleSheet(
      "QPushButton { background-color: #FF6F61; color: white; } "
      "QPushButton:disabled { background-color: #CCCCCC; color: #757575; }");
  actionLayout->addWidget(cancelButton);
  actionLayout->addWidget(addButton);
  mainLayout->addLayout(actionLayout);
  checkTaskNameInput(); // 任务必须有名字，否则禁用按钮
  connect(taskNameEdit, &QLineEdit::textChanged, this,
          &newTaskWidget::checkTaskNameInput);
  TaskDB* taskdb = new TaskDB;
  qDebug() << "taskdb ok";
  /*QPropertyAnimation* propertyAnimation =
      new QPropertyAnimation(this, "geometry");
  propertyAnimation->setEasingCurve(QEasingCurve::InOutQuint)
  propertyAnimation->setDuration(200);*/

  TaskData t;
  connect(addButton, &QPushButton::clicked, this,
          &newTaskWidget::onAddButtonClicked);
  connect(todayButton, &QPushButton::clicked, this,
          &newTaskWidget::onTodayButtonClicked);
  connect(priorityButton, &QPushButton::clicked, this,
          &newTaskWidget::onPriorityButtonClicked);
  connect(remindButton, &QPushButton::clicked, this,
          &newTaskWidget::onRemindButtonClicked);
  connect(upgradeButton, &QPushButton::clicked, this,
          &newTaskWidget::onUpgradeButtonClicked);
  connect(moreButton, &QPushButton::clicked, this,
          &newTaskWidget::onMoreButtonClicked);
  connect(cancelButton, &QPushButton::clicked, this,
          &newTaskWidget::onCancelButtonClicked);

  setAttribute(Qt::WA_DeleteOnClose); // 关闭widget后释放资源
}
void newTaskWidget::onAddButtonClicked() {
  // 在这里添加添加任务按钮被点击时的处理代码
  // 获取控件的内容
  QString taskName =
      taskNameEdit->text(); // todo 如果没写名字则无法添加 按钮是灰的
  QString   description = descriptionEdit->toPlainText();
  QDateTime timeNow     = QDateTime::currentDateTime();
  Snowflake snowflake(0);
  TaskData  task = TaskData{.id              = snowflake.generateId(),
                            .title           = taskName,
                            .content         = description,
                            .createdDateTime = timeNow};
  // ... 获取其他控件的内容 ...
  // ... 保存其他控件的内容 ...
  // 将控件的内容保存到 task 中
  TaskDB    db;
  db.replaceTask(task);
  close();
}
void newTaskWidget::onTodayButtonClicked() {
  calendarWindow->show();
}
void newTaskWidget::onPriorityButtonClicked() {
  // 在这里添加优先级按钮被点击时的处理代码
}
void newTaskWidget::onRemindButtonClicked() {
  // 在这里添加提醒按钮被点击时的处理代码
}
void newTaskWidget::onUpgradeButtonClicked() {
  // 在这里添加升级按钮被点击时的处理代码
}
void newTaskWidget::onMoreButtonClicked() {
  // 在这里添加更多按钮被点击时的处理代码
}
void newTaskWidget::onCancelButtonClicked() {
  close();
}
void newTaskWidget::checkTaskNameInput() {
  bool isInputEmpty = taskNameEdit->text().isEmpty();
  addButton->setDisabled(isInputEmpty);
}
void newTaskWidget::resizeEvent(QResizeEvent* event) {
  // auto width = this->parentWidget()->width();
  //  width和height都是主窗口类的私有变量
  // auto height = this->parentWidget()->height();
  /*propertyAnimation->setStartValue(QRect(-1, 0, 10, height));
  //参数代表左，上，右，下坐标 propertyAnimation->setEndValue(QRect(-1, 0,
  width, height)); if (event->type() == QEvent::HoverEnter)
  //鼠标进入黄色侧边栏中悬浮，正向播动画
      {
          propertyAnimation->setDirection(QAbstractAnimation::Forward);
          propertyAnimation->start();
          return true;
      }
      else if (event->type() == QEvent::HoverLeave)
  //鼠标离开黄色侧边栏，反向播动画
      {
          propertyAnimation->setDirection(QAbstractAnimation::Backward);
          propertyAnimation->start();
          return false;
      }*/
}
CalendarWindow::CalendarWindow(QWidget* parent) : QWidget(parent) {
  mainLayout = new QVBoxLayout(this); // 主布局
  topLayout  = new QHBoxLayout();     // 顶部按钮和标签布局
  dateButton = new QPushButton("6月8日", this);
  topLayout->addWidget(dateButton);
  mainLayout->addLayout(topLayout);

  quickSelectLayout = new QVBoxLayout(); // 快捷日期选择按钮布局
  tomorrowButton    = new QPushButton(QIcon(":/icons/sun.png"), "明天", this);
  quickSelectLayout->addWidget(tomorrowButton);
  nextWeekendButton =
      new QPushButton(QIcon(":/icons/weekend.png"), "下周末", this);
  quickSelectLayout->addWidget(nextWeekendButton);
  nextWeekButton = new QPushButton(QIcon(":/icons/nextweek.png"), "下周", this);
  quickSelectLayout->addWidget(nextWeekButton);
  noDateButton = new QPushButton(QIcon(":/icons/nodate.png"), "没有日期", this);
  quickSelectLayout->addWidget(noDateButton);
  mainLayout->addLayout(quickSelectLayout);

  calendar = new QCalendarWidget(this);
  calendar->setGridVisible(true);
  mainLayout->addWidget(calendar);

  timeLayout = new QHBoxLayout();
  timeButton = new QPushButton(QIcon(":/icons/time.png"), "时间", this);
  timeLayout->addWidget(timeButton);
  mainLayout->addLayout(timeLayout);

  setLayout(mainLayout);
  setWindowTitle("Calendar Widget");
}

PriorityButton::PriorityButton(QWidget* parent) : QPushButton(parent) {
  setText("优先级");
  setupMenu();
}

void PriorityButton::setupMenu() {
  priorityMenu = new QMenu(this);

  /*priority1Action = new QAction(QIcon(":/icons/red_flag.png"), "优先级1",
  this); priority2Action = new QAction(QIcon(":/icons/orange_flag.png"),
  "优先级2", this); priority3Action = new
  QAction(QIcon(":/icons/blue_flag.png"), "优先级3", this); priority4Action =
  new QAction(QIcon(":/icons/white_flag.png"), "优先级4", this);*/
  priority1Action = new QAction(QIcon(":/icons/red_flag.png"), "优先级1", this);
  priority2Action =
      new QAction(QIcon(":/icons/orange_flag.png"), "优先级2", this);
  priority3Action =
      new QAction(QIcon(":/icons/blue_flag.png"), "优先级3", this);
  priority4Action =
      new QAction(QIcon(":/icons/white_flag.png"), "优先级4", this);
  priorityMenu->addAction(priority1Action);
  priorityMenu->addAction(priority2Action);
  priorityMenu->addAction(priority3Action);
  priorityMenu->addAction(priority4Action);

  setMenu(priorityMenu);
}
AddTaskButton::AddTaskButton(QWidget* parent) : QPushButton(parent) {
  QPixmap iconmap;
  iconmap.load("../OneLifeRelief/resource/icon/addbutton.jpg");
  QIcon icon(iconmap);
  this->setIcon(icon);
  this->setMinimumSize(50, 50);
  connect(this, &QPushButton::clicked, [&] {
    taskwidget = new newTaskWidget;
    taskwidget->show();
  });
};
