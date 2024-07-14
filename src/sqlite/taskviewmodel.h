
#ifndef TASKVIEWMODEL_H
#define TASKVIEWMODEL_H
// ViewModel类的设计将遵循MVC架构中ViewModel的角色，即作为Model和View之间的桥梁。
// ViewModel类将负责处理用户界面的逻辑，而不直接与数据库交互，这一任务留给Model类。
// 下面是ViewModel类的基本设计：
// taskviewmodel.h
#include "model/task/taskdata.h"
#include "sqlite/taskdatabasecache.h"
#include <QObject>
#include <qlist.h>
class TaskViewModel : public QObject {
    Q_OBJECT

  public:
    explicit TaskViewModel(TaskData&          _taskData,
                           TaskDatabaseCache* parent = nullptr);

    // ViewModel提供的公共接口
    void loadTasks();                       // 加载所有任务
    void addTask(const TaskData& task);     // 添加任务
    void updateTask(const TaskData& task);  // 更新任务
    void deleteTask(const QString& taskId); // 删除任务

  signals:
    void tasksLoaded(const QList<TaskData>& tasks); // 任务加载完成信号
    void taskAdded(bool success);                   // 任务添加结果信号
    void taskUpdated(bool success);                 // 任务更新结果信号
    void taskDeleted(bool success);                 // 任务删除结果信号

  private:
    TaskData& taskData; // 任务数据
};

#endif // TASKVIEWMODEL_H
