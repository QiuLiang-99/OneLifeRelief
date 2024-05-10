#ifndef TASK_H
#define TASK_H
#include <QString>

#include <QDate>
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
  public:
    Task();

  private:
    // 基础类型
    QString name;
    QString description;
    QString assignee; // 任务的负责人或执行者
    int     progress; // 任务进度

    // 枚举类型
    Status   status;
    Priority priority;
    TaskType taskType;

    // 复杂类型
    struct TaskDateTime {
        QDate createdDate;
        QDate startDate;
        QDate endDate;
    } time;
    QList<Task> subTasks; // 子任务列表
    QStringList tags;     // 标签列表
    QDateTime   reminders;
};
#endif // TASK_H
