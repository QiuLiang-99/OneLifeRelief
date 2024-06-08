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
