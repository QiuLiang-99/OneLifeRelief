#ifndef TASKDB_H
#define TASKDB_H
#include <QObject>

#include "model/task/taskdata.h"
#include "sqlite/taskdatabasecache.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
class TaskDAO : public QObject {
    Q_OBJECT

  public:
    explicit TaskDAO(TaskDatabaseCache& db, QObject* parent = nullptr);
    virtual ~TaskDAO();

  public:
    void saveCachetoDatabase();
    void loadDatabaseintoCache();

  private:
    TaskDatabaseCache& DBcache; // 定义数据库名称
};
#endif                          // TASKDB_H
