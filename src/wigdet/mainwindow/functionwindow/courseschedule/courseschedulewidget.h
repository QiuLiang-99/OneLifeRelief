#ifndef __COURSESCHEDULEWIDGET_H__
#define __COURSESCHEDULEWIDGET_H__
#include "courseschedule.h"
#include "include/QTUI.h"
#include "wigdet/universalwigdet/newtask/newtask.h"

class CourseScheduleWidget : public QWidget {
    Q_OBJECT

  public:
    explicit CourseScheduleWidget(QWidget* parent = nullptr) : QWidget(parent) {
      QVBoxLayout* pageLayout = new QVBoxLayout(this);
      pageLayout->setSpacing(0); // 表示各个控件之间的上下间距
      pageLayout->setContentsMargins(0, 0, 0, 0);
      QPushButton* importBtn = new QPushButton("导入");
      pageLayout->addWidget(importBtn);
      connect(importBtn, &QPushButton::clicked, this, [=]() {
        newTaskWidget* newTask = new newTaskWidget(this);
        newTask->show();
      });
      CourseScheduleView* ScheduleView = new CourseScheduleView(this);
      pageLayout->addWidget(ScheduleView);
    };
    //~CourseScheduleWidget();
};
#endif // __COURSESCHEDULEWIDGET_H__