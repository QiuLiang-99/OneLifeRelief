#include "taskdb.h"

TaskDB::TaskDB(QWidget* parent) : QWidget(parent) {

  // 打开数据库
  DB = QSqlDatabase::addDatabase("QSQLITE");
  DB.setDatabaseName("./TaskDB.db"); // 设置数据库名称
  if (DB.open()) {
    qDebug() << "Database opened successfully！";
  } else {
    qDebug() << "无法打开数据库：" << DB.lastError().text();
  }
  // 创建一个QSqlQuery对象，用于执行SQL命令
  QSqlQuery query;

  // 执行SQL命令来创建一个名为"Tasks"的表
  // 使用R"(
  // )"来创建一个原始字符串，这样就可以在字符串中直接使用引号和反斜杠，而不需要转义它们
  // 使用IF NOT EXISTS来确保如果"Tasks"表已经存在，那么CREATE
  // TABLE命令不会做任何事情
  bool success = query.exec(
      R"(CREATE TABLE IF NOT EXISTS Tasks (
    id INTEGER PRIMARY KEY, // 创建一个名为"id"的字段，数据类型为整数（INTEGER），并将其设置为主键（PRIMARY KEY）
    name TEXT, // 创建一个名为"name"的字段，数据类型为文本（TEXT），该字段可以为空
    description TEXT, // 创建一个名为"description"的字段，数据类型为文本（TEXT），该字段可以为空
    assignee TEXT, // 创建一个名为"assignee"的字段，数据类型为文本（TEXT），该字段可以为空
    progress INTEGER, // 创建一个名为"progress"的字段，数据类型为整数（INTEGER），该字段可以为空
    status INTEGER, // 创建一个名为"status"的字段，数据类型为整数（INTEGER），该字段可以为空
    priority INTEGER, // 创建一个名为"priority"的字段，数据类型为整数（INTEGER），该字段可以为空
    taskType INTEGER, // 创建一个名为"taskType"的字段，数据类型为整数（INTEGER），该字段可以为空
    createdDate TEXT, // 创建一个名为"createdDate"的字段，数据类型为文本（TEXT），该字段可以为空
    startDate TEXT, // 创建一个名为"startDate"的字段，数据类型为文本（TEXT），该字段可以为空
    endDate TEXT, // 创建一个名为"endDate"的字段，数据类型为文本（TEXT），该字段可以为空
    reminders TEXT // 创建一个名为"reminders"的字段，数据类型为文本（TEXT），该字段可以为空
    ))"); // 结束SQL命令的字符串

  // 检查SQL命令是否执行成功
  if (!success) {
    // 如果SQL命令执行失败，打印错误信息
    qDebug() << "Error creating Tasks table: " << query.lastError().text();
  }
  if (success) {
    qDebug() << "Table created successfully!";
  } else {
    qDebug() << "Failed to create table: " << query.lastError().text();
  }
  Add();     // 添加数据
  Select();  // 查询数据
  Update();  // 更新数据
  Delete();  // 删除数据

  FastAdd(); // 对大量数据进行快速添加，尝试过添加几千条数据，不到一秒就添加完成
}

void TaskDB::Add() // 增
{
  /*
   * 在班级表中添加数据,
     添加的数据为
     班级名称：一班
     班主任：李主任
     班级人数：25
  */
  queryString = QString("insert into class(class_name, class_teacher "
                        ",student_number) values('%1','%2',%3) ")
                    .arg("一班")
                    .arg("李主任")
                    .arg(25);
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
  queryString =
      QString("delete from class where class_name = '%1'").arg("一班");
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
  queryString = QString("update class set class_teacher='%1' "
                        ",student_number=%2 where class_name='%3' ")
                    .arg("张主任")
                    .arg(30)
                    .arg("一班");
  QSqlQuery query;
  if (query.exec(queryString)) {
    qDebug() << "updata data Successful!";
  } else {
    qDebug() << "updata data Failed!";
  }
}

void TaskDB::Select() // 查
{
  queryString =
      QString("select * from class where class_name = '%1'").arg("一班");
  QSqlQuery query(queryString);
  while (query.next()) {
    QString class_teacher  = query.value("class_teacher").toString();
    int     student_number = query.value("student_number").toInt();
    qDebug() << "班主任：" << class_teacher;
    qDebug() << "班级人数：" << student_number;
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
