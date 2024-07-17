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
/*
// 使用std::is_same_v在概念中直接检查类型是否为TaskData
template <typename T>
concept IsTaskData = std::is_same_v<T, TaskData>;

// 使用requires子句应用IsTaskData概念来约束模板参数
template <typename Container>
  requires IsTaskData<typename Container::value_type>
void FunctionOnlyForTaskDataContainer(const Container& ) {
  qDebug() << "FunctionOnlyForTaskDataContainer";
}*/
class TaskDAO : public QObject {
    Q_OBJECT

  public:
    explicit TaskDAO(TaskDatabaseCache& db, QObject* parent = nullptr);
    virtual ~TaskDAO();

  public:
    void saveCachetoDatabase();
    void loadDatavaseintoCache();

  private:
    TaskDatabaseCache& DBcache; // 定义数据库名称
};
#endif                          // TASKDB_H
