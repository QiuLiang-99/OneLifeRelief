#include "taskdb.h"

TaskDB::TaskDB(QWidget* parent) : QWidget(parent) {
  QSqlDatabase db;
  if (QSqlDatabase::contains("qt_sql_default_connection")) {
    db = QSqlDatabase::database("qt_sql_default_connection");
  } else {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("TaskDB.db");
  }

  if (db.open()) {
    qDebug() << "Database opened successfully！";
  } else {
    qDebug() << "无法打开数据库：" << db.lastError().text();
  }

  // 创建一个QSqlQuery对象，用于执行SQL命令
  QSqlQuery query;

  // 使用原始字符串文字(R"()")来避免转义字符问题
  QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS Task (
            id INTEGER PRIMARY KEY, 
            name TEXT, 
            description TEXT, 
            assignee TEXT, 
            progress INTEGER, 
            status INTEGER, 
            priority INTEGER, 
            taskType INTEGER, 
            createdDate TEXT, 
            startDate TEXT, 
            endDate TEXT, 
            reminders TEXT
        )
    )";

  // 执行SQL命令来创建一个名为"Tasks"的表
  bool success             = query.exec(createTableQuery);

  if (success) {
    qDebug() << "Table 'Tasks' created or already exists.";
  } else {
    qDebug() << "Failed to create table 'Tasks':" << query.lastError().text();
  }

  // 关闭数据库
  db.close();

  addTask(); // 添加数据
}
void TaskDB::addOrUpdateTask(int            id,
                             const QString& name,
                             const QString& description
                             /* 其他参数 */) {
  QSqlQuery query;
  query.prepare("SELECT * FROM Task WHERE id = :id");
  query.bindValue(":id", id);
  if (!query.exec()) {
    qDebug() << "查询任务失败：" << query.lastError().text();
    return;
  }

  if (query.next()) {
    // 如果存在具有相同主键的任务，执行更新操作
    QString updateSql = QString("UPDATE Task SET name='%1', description='%2', "
                                "/* 其他字段 */ WHERE id=%3")
                            .arg(name)
                            .arg(description)
                            /* .arg(其他值) */
                            .arg(id);
    if (!query.exec(updateSql)) {
      qDebug() << "更新任务失败：" << query.lastError().text();
    }
  } else {
    // 如果不存在具有相同主键的任务，执行添加操作
    QString insertSql =
        QString("INSERT INTO Task (id, name, description, /* 其他字段 */) "
                "VALUES (%1, '%2', '%3', /* 其他值 */)")
            .arg(id)
            .arg(name)
            .arg(description)
        /* .arg(其他值) */;
    if (!query.exec(insertSql)) {
      qDebug() << "添加任务失败：" << query.lastError().text();
    }
  }
}
void TaskDB::addTask() // 增
{
  /*
   * 在班级表中添加数据,
     添加的数据为
     班级名称：一班
     班主任：李主任
     班级人数：25
  */
  queryString =
      QString(
          "insert into Task (name, description, assignee, progress, status, "
          "priority, taskType, createdDate, startDate, endDate, reminders) "
          "VALUES('%1','%2','%3',%4,%5,%6,%7,'%8','%9','%10','%11')")
          .arg("新任务")
          .arg("这是一个新任务")
          .arg("张三")
          .arg(0)
          .arg(1)
          .arg(2)
          .arg(1)
          .arg("2022-01-01")
          .arg("2022-01-02")
          .arg("2022-01-03")
          .arg("2022-01-02");
  QSqlQuery query; // 执行sql语句
  if (query.exec(queryString)) {
    qDebug() << "insert data Successful!";
  } else {
    qDebug() << "insert data Failed!";
  }
}

void TaskDB::Delete() // 删
{
  // 在这里有时候要判断限制条件是否为空，这时候可以用这个sql语句，当班级名称不为空时删除
  // queryString = QString("delete from class where class_name is not null");
  queryString = QString("DELETE FROM Task WHERE id = %1").arg(1);
  QSqlQuery query(queryString);
  if (query.exec()) {
    qDebug() << "Delete data Successful!";
  } else {
    qDebug() << "Delete data Failed!";
  }
}

void TaskDB::Update() // 改
{
  // 更新数据，将班级名称作为限制条件进行数据更新
  queryString =
      QString(
          "UPDATE Task SET name='%1', description='%2', assignee='%3', "
          "progress=%4, status=%5, priority=%6, taskType=%7, createdDate='%8', "
          "startDate='%9', endDate='%10', reminders='%11' WHERE id=%12")
          .arg("新任务")
          .arg("这是一个新任务")
          .arg("张三")
          .arg(0)
          .arg(1)
          .arg(2)
          .arg(1)
          .arg("2022-01-01")
          .arg("2022-01-02")
          .arg("2022-01-03")
          .arg("2022-01-02")
          .arg(1);
  QSqlQuery query;
  if (query.exec(queryString)) {
    qDebug() << "updata data Successful!";
  } else {
    qDebug() << "updata data Failed!";
  }
}

void TaskDB::Select() // 查
{
  queryString = QString("SELECT * FROM Task WHERE id = %1").arg(1);
  QSqlQuery query(queryString);
  while (query.next()) {
    QString name        = query.value("name").toString();
    QString description = query.value("description").toString();
    // ... 获取其他字段的值 ...
    qDebug() << "任务名称：" << name;
    qDebug() << "任务描述：" << description;
    // ... 打印其他字段的值 ...
  }
}
// 对大量数据进行快速添加，尝试过添加几千条数据，不到一秒就添加完成
void TaskDB::FastAdd() {
  // 使用事务
  DB.transaction(); // 开启事务
  QSqlQuery query;
  query.prepare("INSERT INTO class (class_name, class_teacher, student_number) "
                "VALUES (?, ?, ?)");
  for (int i = 0; i < 100; ++i) {
    query.bindValue(0, "二班");
    query.bindValue(1, "张三");
    query.bindValue(2, i);
    query.exec();
  }
  DB.commit(); // 一次性提交，省去大量时间
}
