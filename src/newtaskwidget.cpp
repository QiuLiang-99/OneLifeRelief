#include "newTaskWidget.h"
#include "src/taskdb.h"

#include <QLineEdit>
#include <QPropertyAnimation>
#include <qabstractspinbox.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

newTaskWidget::newTaskWidget(QWidget* parent) : QDialog(parent) {
  setWindowModality(Qt::WindowModal);
  QVBoxLayout* layout   = new QVBoxLayout(this);
  QLineEdit*   nameline = new QLineEdit;
  nameline->setPlaceholderText("任务名称"); // 设置淡色提示字
  QFont font;
  font.setPointSize(12);                    // 字号大小
  // font.setFamily(("wenquanyi"));            // 字体样式
  font.setBold(false);
  nameline->setFont(font);
  layout->addWidget(nameline);
  QLineEdit* describeline = new QLineEdit;
  describeline->setPlaceholderText("描述"); // 设置淡色提示字
  layout->addWidget(describeline);
  QPushButton* cancelBtn  = new QPushButton("取消");

  QPushButton* confirmBtn = new QPushButton("添加任务");

  TaskDB* taskdb          = new TaskDB;
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
