#ifndef TASKDATA_H
#define TASKDATA_H
#include <QDate>
#include <QString>
#include <qcontainerfwd.h>
#include <qdatetime.h>

namespace TaskEnums {
  enum Priority { // todo 紧急 重要
    TOP,
    HIGH,
    LOWER,
    WAIT
  };
  // book sport

  enum TaskType {
    Notype,
    STUDY,  // 学习
    WORK,   // 工作
    EXAM,   // 考试 游戏
    HABIT,  // 习惯
    CINEMA, // 电影
    TRIP,   // 旅游
  };
  enum Status {
    NoStatus,
    Backlog,    // This item hasn't been started #DAFBE1 #1F883D
    Ready,      // This is ready to be picked up #DDF4FF #0969DA
    InProgress, // This is actively being worked on #FFF8C5 #9A6700
    Inreview,   // This item is in review  #FBEFFF #8250DF
    Done,       // This has been completed #FFF1E5 #BC4C00
    Todo,       // #DAFBE1 #1F883D
    NotPlanned, // This is not planned currently #FFEFF7 #BF3989
  };
} // namespace TaskEnums
struct TaskData {

    unsigned id;
    QString  projectId;
    int      imgMode;
    QString  parentId;

    QString             title;
    QString             content;
    QString             assignee; // 任务的负责人或执行者
    int                 progress; // 任务进度
    int                 deleted;
    // 枚举 TEXT or NOTE(task or note)
    //  枚举类型
    TaskEnums::Status   status;
    TaskEnums::Priority priority;
    TaskEnums::TaskType taskType;

    QDateTime   createdDateTime;
    QDateTime   startDateTime;
    QDateTime   modifiedTime;
    QDateTime   completedTime;
    // QList<TaskData> subTasks; // 子任务列表
    QStringList tags; // 标签列表
    QDateTime   reminderTime;
    QStringList childrenString;

  public:
    inline QString QDateTimetoQString(const QDateTime& time) const {
      return time.toString("yyyy-MM-dd hh:mm:ss");
    }
    inline QDateTime QStringtoQDateTime(const QString& str) const {
      return QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
    }
};
#endif // TASKDATA_H
