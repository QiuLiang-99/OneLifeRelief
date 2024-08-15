#include "taskdatabasecache.h"
#include "sqlite/taskdao.h"
#include "sqlite/taskdatabasecache.h"

#include <QGlobalStatic>
Q_GLOBAL_STATIC(TaskDatabaseCache, taskDatabaseCache)

TaskDatabaseCache::TaskDatabaseCache(QObject* parent) : QObject(parent) {}
TaskList& TaskDatabaseCache::data() { return taskDatabaseCache->taskList; }
TaskDatabaseCache::~TaskDatabaseCache() {
  TaskDAO dao(*this);
  for (auto& task : taskDatabaseCache->data()) {
    qDebug() << task.id;
    qDebug() << task.title;
  } // todo 存了就不要再存一次了
  dao.saveCachetoDatabase();
}