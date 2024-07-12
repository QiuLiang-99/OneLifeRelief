#ifndef TASKDB_H
#define TASKDB_H
#include <QObject>

#include "model/task/taskdata.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <qlist.h>

class TaskDB : public QObject {
    Q_OBJECT

  public:
    explicit TaskDB(QObject* parent = nullptr);
    virtual ~TaskDB();

  public:
    bool    createTable(); // 创建表
    // 定义一个变量，用于增删改查
    QString queryString;

    bool addTask(const TaskData&); // 添加数据，不支持大量数据快速添加
    bool Delete(); // 删除数据，支持大量数据快速删除
    bool Update(); // 更新数据，若更新大量数据，可以先快速删除后在快速添加
    bool            Select(); // 查询数据，支持大量数据快速查询
    QList<TaskData> loadAllTask();
    bool            replaceTask(const TaskData&);
    bool            FastAdd(); // 在sqlite中快速添加大量数据

  private:
    QSqlDatabase DB; // 定义数据库名称
};
#endif               // TASKDB_H
