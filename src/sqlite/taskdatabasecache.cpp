#include "taskdatabasecache.h"

TaskDatabaseCache::TaskDatabaseCache(QObject* parent) : QObject(parent) {}
Q_GLOBAL_STATIC(TaskDatabaseCache, taskDatabaseCache);
TaskDatabaseCache& getSingleton() { return *taskDatabaseCache; }