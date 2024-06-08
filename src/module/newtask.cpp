#include "newTask.h"
#include "src/module/sqlite/taskdb.h"

#include <QLineEdit>
#include <QPropertyAnimation>
#include <qabstractspinbox.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

newTaskWidget::newTaskWidget(QWidget* parent) : QDialog(parent) {
  setWindowModality(Qt::WindowModal);
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
  addButton->setStyleSheet("background-color: #FF6F61; color: white;");
  actionLayout->addWidget(cancelButton);
  actionLayout->addWidget(addButton);
  mainLayout->addLayout(actionLayout);

  TaskDB* taskdb = new TaskDB;
  qDebug() << "taskdb ok";
  /*QPropertyAnimation* propertyAnimation =
      new QPropertyAnimation(this, "geometry");
  propertyAnimation->setEasingCurve(QEasingCurve::InOutQuint)
  propertyAnimation->setDuration(200);*/
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
  // 主布局
  QVBoxLayout* mainLayout = new QVBoxLayout(this);

  // 顶部按钮和标签布局
  QHBoxLayout* topLayout  = new QHBoxLayout();
  QPushButton* dateButton = new QPushButton("6月8日", this);
  topLayout->addWidget(dateButton);
  mainLayout->addLayout(topLayout);

  // 快捷日期选择按钮布局
  QVBoxLayout* quickSelectLayout = new QVBoxLayout();

  QPushButton* tomorrowButton =
      new QPushButton(QIcon(":/icons/sun.png"), "明天", this);
  quickSelectLayout->addWidget(tomorrowButton);

  QPushButton* nextWeekendButton =
      new QPushButton(QIcon(":/icons/weekend.png"), "下周末", this);
  quickSelectLayout->addWidget(nextWeekendButton);

  QPushButton* nextWeekButton =
      new QPushButton(QIcon(":/icons/nextweek.png"), "下周", this);
  quickSelectLayout->addWidget(nextWeekButton);

  QPushButton* noDateButton =
      new QPushButton(QIcon(":/icons/nodate.png"), "没有日期", this);
  quickSelectLayout->addWidget(noDateButton);

  mainLayout->addLayout(quickSelectLayout);

  // 日历控件
  QCalendarWidget* calendar = new QCalendarWidget(this);
  calendar->setGridVisible(true);
  mainLayout->addWidget(calendar);

  // 时间按钮布局
  QHBoxLayout* timeLayout = new QHBoxLayout();
  QPushButton* timeButton =
      new QPushButton(QIcon(":/icons/time.png"), "时间", this);
  timeLayout->addWidget(timeButton);
  mainLayout->addLayout(timeLayout);

  setLayout(mainLayout);
  setWindowTitle("Calendar Widget");
}