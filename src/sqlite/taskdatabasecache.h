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

    TaskList& data();

  private:
    TaskList taskList = {};
};

#endif // TASKDATABASECACHE_H