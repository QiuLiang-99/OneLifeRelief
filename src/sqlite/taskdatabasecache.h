#ifndef TASKDATABASECACHE_H
#define TASKDATABASECACHE_H

#include "sqlite/model/task/taskdata.h"
#include <QList>
#include <qmap.h>
#include <qtypes.h>
using TaskList = QList<TaskData>;

// 任务数据库缓存类
class TaskDatabaseCache : public QObject {
    Q_OBJECT

  public:
    explicit TaskDatabaseCache(QObject* parent = nullptr);
    ~TaskDatabaseCache();

    inline TaskList& data() { return taskList; }

    // 添加任务数据
    /*void addTask(const TaskData& task) { taskList.append(task); }

    // 删除任务数据
    bool removeTask(const TaskData& task) { return taskList.removeOne(task); }

    // 查找任务数据
    // 这里只是一个示例，具体实现需要根据 TaskData 的结构来设计
    TaskData* findTask(int id) {
      for (auto& task : taskList) {
        if (task.id == id) { // 假设 TaskData 有一个名为 id 的成员变量
          return &task;
        }
      }
      return nullptr;
    }*/

  public:
    static TaskDatabaseCache& getSingleton();

  private:
    TaskList taskList = {};
    // QMap<qulonglong, TaskData&> taskIDIndex = {};
    // QMap<quint64, int> taskIDIndex = {};
    // todo
};
#endif // TASKDATABASECACHE_H