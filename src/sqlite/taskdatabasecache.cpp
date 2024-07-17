#include "taskdatabasecache.h"
#include "sqlite/taskdao.h"

TaskDatabaseCache::TaskDatabaseCache(QObject* parent) : QObject(parent) {
  TaskDAO dao(*this);
  dao.loadDatabaseintoCache();
}
TaskDatabaseCache::~TaskDatabaseCache() {
  TaskDAO dao(*this);
  for (auto& task : TaskDatabaseCache::getSingleton().data()) {
    qDebug() << task.id;
    qDebug() << task.title;
  }
  dao.saveCachetoDatabase();
}

Q_GLOBAL_STATIC(TaskDatabaseCache, taskDatabaseCache);
TaskDatabaseCache& TaskDatabaseCache::getSingleton() {
  return *taskDatabaseCache;
}