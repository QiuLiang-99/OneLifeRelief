#ifndef NEWTASKWIDGET_H
#define NEWTASKWIDGET_H
#include <QCoreApplication>
#include <QDialog>
#include <QFile>
#include <QPainter>
#include <QWidget>
#include <qabstractbutton.h>
#include <qdatetime.h>
#include <qicon.h>
#include <qpushbutton.h>
#include <qsize.h>

enum class Priority { // todo 紧急 重要
  TOP,
  HIGH,
  LOWER,
  WAIT
};
// book sport
enum class TaskType {
  Notype,
  STUDY,            // 学习
  WORK,             // 工作
  EXAM,             // 考试
  HABIT,            // 习惯
  CINEMA,           // 电影
  TRIP,             // 旅游
};
enum class Status { /*name inside outside*/
  NoStatus,
  Backlog,          // This item hasn't been started #DAFBE1 #1F883D
  Ready,            // This is ready to be picked up #DDF4FF #0969DA
  InProgress,       // This is actively being worked on #FFF8C5 #9A6700
  Inreview,         // This item is in review  #FBEFFF #8250DF
  Done,             // This has been completed #FFF1E5 #BC4C00
  Todo,             // #DAFBE1 #1F883D
  NotPlanned,       // This is not planned currently #FFEFF7 #BF3989
};
struct Task {
  private:
    QString name;
    QString description;
    struct TaskDateTime {
        QDate createdDate;
        QDate startDate;
        QDate endDate;
    } time;
    Status    status;
    Priority  priority;
    TaskType  taskType;
    // todo 标签功能
    QDateTime reminders;
};
class NewTaskWidget : public QDialog {
    Q_OBJECT

  public:
    explicit NewTaskWidget(QWidget* parent = nullptr);

  protected:
    void resizeEvent(QResizeEvent* event);

  signals:
};
class AddTaskButton : public QPushButton {
    Q_OBJECT

  public:
    explicit AddTaskButton(QWidget* parent = nullptr) : QPushButton(parent) {
      QPixmap iconmap;
      iconmap.load("../OneLifeRelief/resource/icon/addbutton.jpg");
      QIcon icon(iconmap);
      this->setIcon(icon);
      this->setMinimumSize(50, 50);
      connect(this, &QPushButton::clicked, this, [&] {
        taskwidget = new NewTaskWidget;
        taskwidget->show();
      });
    };

    // void paintEvent(QPaintEvent* event) override {}

  private:
    NewTaskWidget* taskwidget;
};

#endif // NEWTASKWIDGET_H
