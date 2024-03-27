#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/CourseScheduleView.h"
#include "src/taskandGoalView.h"
#include "src/timeline.h"
#include <QLabel>
#include <QStackedWidget>
#include <QWidget>
#include <qboxlayout.h>
#include <qframe.h>
#include <qpushbutton.h>
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
    void newPage(QWidget*, const QString&, const int&);
    void setupUI();

  protected:
    virtual void resizeEvent(QResizeEvent* event) override;

  private:
    void            newWidget();
    QGridLayout*    gridLayout;
    QGridLayout*    buttonlayout;
    QButtonGroup*   tablebtnGroup;
    QStackedWidget* mainWidget;

  private slots:
    void on_test_clicked();
};
class CourseScheduleWidget : public QWidget {
    Q_OBJECT

  public:
    explicit CourseScheduleWidget(QWidget* parent = nullptr) : QWidget(parent) {
      QHBoxLayout* pageLayout = new QHBoxLayout(this);
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
      QHBoxLayout*     pageLayout = new QHBoxLayout(this);
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
      QHBoxLayout* pageLayout = new QHBoxLayout(this);
      QPushButton* test       = new QPushButton(this);
      pageLayout->setSpacing(0); // 表示各个控件之间的上下间距
      pageLayout->setContentsMargins(0, 0, 0, 0);
      pageLayout->addWidget(test);
      Timeline* timeLine = new Timeline(this);
      pageLayout->addWidget(timeLine);
      // connect(test, &QPushButton::clicked, this,
      // &MainWindow::on_test_clicked);
    };
    //~TimeLineWidget();
};

#endif // MAINWINDOW_H
