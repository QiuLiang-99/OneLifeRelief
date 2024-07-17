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
// 使用std::is_same_v在概念中直接检查类型是否为TaskData
template <typename T>
concept IsTaskData = std::is_same_v<T, TaskData>;

// 使用requires子句应用IsTaskData概念来约束模板参数
template <typename Container>
  requires IsTaskData<typename Container::value_type>
void FunctionOnlyForTaskDataContainer(const Container& /*container*/) {
  qDebug() << "FunctionOnlyForTaskDataContainer";
}
class TaskDAO : public QObject {
    Q_OBJECT

  public:
    explicit TaskDAO(TaskDatabaseCache& db, QObject* parent = nullptr);
    virtual ~TaskDAO();

  public:
    // 定义一个变量，用于增删改查
    QString queryString;

    bool addTask(const TaskData&); // 添加数据，不支持大量数据快速添加
    bool Delete(); // 删除数据，支持大量数据快速删除
    bool Update(); // 更新数据，若更新大量数据，可以先快速删除后在快速添加
    bool            Select(); // 查询数据，支持大量数据快速查询
    QList<TaskData> loadAllTask();
    bool            replaceTask(const TaskData&);

  private:
    TaskDatabaseCache& DBcache; // 定义数据库名称
};
#endif                          // TASKDB_H
