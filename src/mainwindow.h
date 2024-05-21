#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/CourseScheduleView.h"
#include "src/newtaskwidget.h"
#include "src/taskandGoalView.h"
#include "src/timeline.h"
#include <QLabel>
#include <QStackedWidget>
#include <QWidget>
#include <qboxlayout.h>
#include <qframe.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qsize.h>
#include <qtmetamacros.h>
#include <qwidget.h>

#include <QButtonGroup>

class MainWindow : public QWidget {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  public:
    void newPage(const QString&);

  protected:
    virtual void resizeEvent(QResizeEvent* event) override;

  public:
    void            setupUI();
    QGridLayout*    gridLayout;
    QGridLayout*    buttonlayout;
    QStackedWidget* mainWidget;
    QButtonGroup*   tablebtnGroup;

    QHBoxLayout* btnHLayout;
    QVBoxLayout* btnVLayout;
  private slots:
    void on_test_clicked();
};
class CourseScheduleWidget : public QWidget {
    Q_OBJECT

  public:
    explicit CourseScheduleWidget(QWidget* parent = nullptr) : QWidget(parent) {
      QVBoxLayout* pageLayout = new QVBoxLayout(this);
      pageLayout->setSpacing(0); // 表示各个控件之间的上下间距
      pageLayout->setContentsMargins(0, 0, 0, 0);
      CourseScheduleView* ScheduleView = new CourseScheduleView(this);
      pageLayout->addWidget(ScheduleView);
    };
    //~CourseScheduleWidget();
};
class taskandGoalWidget : public QWidget {
    Q_OBJECT

  public:
    explicit taskandGoalWidget(QWidget* parent = nullptr) : QWidget(parent) {
      QVBoxLayout*     pageLayout = new QVBoxLayout(this);
      taskandGoalView* taskView   = new taskandGoalView;
      pageLayout->setSpacing(0); // 表示各个控件之间的上下间距
      pageLayout->setContentsMargins(0, 0, 0, 0);
      pageLayout->addWidget(taskView);
    };
    //~taskandGoalWidget();
};
class TimeLineWidget : public QWidget {
    Q_OBJECT

  public:
    explicit TimeLineWidget(QWidget* parent = nullptr) : QWidget(parent) {
      QVBoxLayout* pageLayout               = new QVBoxLayout(this);
      QScrollArea* scrollArea               = new QScrollArea;
      QWidget*     scrollAreaWidgetContents = new QWidget;
      QVBoxLayout* scorllAreaLayout         = new QVBoxLayout;
      Timeline*    timeLine                 = new Timeline;

      pageLayout->setSpacing(0); // 表示各个控件之间的上下间距
      pageLayout->setContentsMargins(0, 0, 0, 0);

      scrollAreaWidgetContents->setGeometry(0, 0, 5000, 100);
      scrollAreaWidgetContents->setLayout(scorllAreaLayout);

      scorllAreaLayout->addWidget(timeLine);

      pageLayout->addWidget(new AddTaskButton);
      pageLayout->addWidget(scrollArea);

      timeLine->setVisible(true);
      scrollArea->setWidget(scrollAreaWidgetContents);
      // connect(test, &QPushButton::clicked, this,
      // &MainWindow::on_test_clicked);
    };
    //~TimeLineWidget();
};
#endif // MAINWINDOW_H
