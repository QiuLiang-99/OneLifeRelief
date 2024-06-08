#ifndef TASK_H
#define TASK_H
#include <QWidget>

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class TaskDB : public QWidget {
    Q_OBJECT

  public:
    TaskDB(QWidget* parent = nullptr);

    // 定义一个变量，用于增删改查
    QString queryString;

    void addTask(); // 添加数据，不支持大量数据快速添加
    void Delete();  // 删除数据，支持大量数据快速删除
    void Update(); // 更新数据，若更新大量数据，可以先快速删除后在快速添加
    void Select(); // 查询数据，支持大量数据快速查询
    void addOrUpdateTask(int            id,
                         const QString& name,
                         const QString& description /* 其他参数 */);
    void FastAdd(); // 在sqlite中快速添加大量数据

  private:
    QSqlDatabase DB; // 定义数据库名称
};
#endif               // TASK_H
