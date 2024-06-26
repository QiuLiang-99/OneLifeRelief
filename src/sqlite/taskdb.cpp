#include "taskdb.h"
#include "src/model/task/taskdata.h"

TaskDB::TaskDB(QObject* parent) : QObject(parent) {
  if (QSqlDatabase::contains("qt_sql_default_connection")) {
    DB = QSqlDatabase::database("qt_sql_default_connection");
  } else {
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("TaskDB.db");
  }
  if (DB.open()) {
    qDebug() << "Database opened successfully！";
  } else {
    qDebug() << "无法打开数据库：" << DB.lastError().text();
  }
  createTable();
  // addTask(); // 添加数据
}
TaskDB::~TaskDB() {
  if (DB.isOpen()) {
    DB.close();
  }
}
bool TaskDB::createTable() {
  QSqlQuery query;
  // 使用原始字符串文字(R"()")来避免转义字符问题
  QString   createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS Task (
            id TEXT PRIMARY KEY, 
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
  bool success               = query.exec(createTableQuery);
  if (success) {
    qDebug() << "Table 'Task' created or already exists.";
  } else {
    qDebug() << "Failed to create table 'Tasks':" << query.lastError().text();
  }
  return success;
}
bool TaskDB::replaceTask(const TaskData& task) {
  // clang-format off
  // ^^^ 注意空格 vvv
  QSqlQuery query;
  query.prepare("REPLACE INTO Task (id, name, description, assignee, progress, status, "
        "priority, taskType, createdDate, startDate, endDate, reminders) "
        "VALUES (:id, :name, :description, :assignee, :progress, :status, "
        ":priority, :taskType, :createdDate, :startDate, :endDate, :reminders)");
  
  query.bindValue(":id", task.id); // 假设task对象有一个id属性
  query.bindValue(":name", task.title);
  query.bindValue(":description", task.content);
  query.bindValue(":assignee", "张三");
  query.bindValue(":progress", -1);
  query.bindValue(":status", -1);
  query.bindValue(":priority", -1);
  query.bindValue(":taskType", -1);
  query.bindValue(":createdDate", task.QDateTimetoQString(task.createdDateTime));
  query.bindValue(":startDate", task.QDateTimetoQString(task.startDateTime));
  query.bindValue(":endDate", task.QDateTimetoQString(task.completedTime));
  query.bindValue(":reminders", task.QDateTimetoQString(task.reminderTime));
  // clang-format on
  // 执行sql语句
  bool success = query.exec();
  if (success) {
    qDebug() << "REPLACE data Successful!";
  } else {
    qDebug() << "REPLACE data Failed!";
  }
  return success;
}
bool TaskDB::addTask(const TaskData& task) {
  // clang-format off
  // ^^^ 注意空格 vvv
  queryString =
      QString("insert into Task (name, description, assignee, progress, status,"
          "priority, taskType, createdDate, startDate, endDate, reminders) "
          "VALUES('%1','%2','%3',%4,%5,%6,%7,'%8','%9','%10','%11')")
          .arg(task.title)
          .arg(task.content)
          .arg("张三") // 任务指定人 （多人任务有用，目前留空）
          .arg(-1)      // progress 任务进度 需要枚举定义？
          .arg(-1)      // status 任务状态 需要枚举定义？
          .arg(-1)      // priority 任务优先级 需要枚举定义？
          .arg(-1)      // taskType 任务类型 需要枚举定义？
          .arg(task.QDateTimetoQString(task.createdDateTime)) // createdDate 创建日期
          .arg(task.QDateTimetoQString(task.startDateTime)) // startDate 开始日期
          .arg(task.QDateTimetoQString(task.completedTime)) // endDate 结束日期
          .arg(task.QDateTimetoQString(task.reminderTime)) // reminders 提醒日期/
      ;
  // clang-format on
  QSqlQuery query; // 执行sql语句
  bool      success = query.exec(queryString);

  if (success) {
    qDebug() << "insert data Successful!";
  } else {
    qDebug() << "insert data Failed!";
  }
  return success;
}

bool TaskDB::Delete() // 删
{
  // 在这里有时候要判断限制条件是否为空，这时候可以用这个sql语句，当班级名称不为空时删除
  // queryString = QString("delete from class where class_name is not null");
  queryString = QString("DELETE FROM Task WHERE id = %1").arg(1);
  QSqlQuery query(queryString);
  bool      success = query.exec();
  if (success) {
    qDebug() << "Delete data Successful!";
  } else {
    qDebug() << "Delete data Failed!";
  }
  return success;
}

bool TaskDB::Update() // 改
{
  // 更新数据，将班级名称作为限制条件进行数据更新
  queryString =
      QString("UPDATE Task SET name='%1', description='%2', assignee='%3', "
              "progress=%4, status=%5, priority=%6, taskType=%7, "
              "createdDate='%8', "
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
  bool      success = query.exec(queryString);
  if (success) {
    qDebug() << "updata data Successful!";
  } else {
    qDebug() << "updata data Failed!";
  }
  return success;
}

bool TaskDB::Select() // 查
{
  queryString = QString("SELECT * FROM Task WHERE id = %1").arg(1);
  QSqlQuery query(queryString);
  while (query.next()) {
    QString id          = query.value("id").toString();
    QString name        = query.value("name").toString();
    QString description = query.value("description").toString();
    QString assignee    = query.value("assignee").toString();
    int     progress    = query.value("progress").toInt();
    int     status      = query.value("status").toInt();
    int     priority    = query.value("priority").toInt();
    int     taskType    = query.value("taskType").toInt();
    QString createdDate = query.value("createdDate").toString();
    QString startDate   = query.value("startDate").toString();
    QString endDate     = query.value("endDate").toString();
    QString reminders   = query.value("reminders").toString();

    qDebug() << "任务ID：" << id;
    qDebug() << "任务名称：" << name;
    qDebug() << "任务描述：" << description;
    qDebug() << "任务分配给：" << assignee;
    qDebug() << "任务进度：" << progress;
    qDebug() << "任务状态：" << status;
    qDebug() << "任务优先级：" << priority;
    qDebug() << "任务类型：" << taskType;
    qDebug() << "任务创建日期：" << createdDate;
    qDebug() << "任务开始日期：" << startDate;
    qDebug() << "任务结束日期：" << endDate;
    qDebug() << "任务提醒：" << reminders;
  }
  return true;
}
QList<TaskData> TaskDB::loadAllTask() // 查
{
  QList<TaskData> taskList;
  queryString = QString("SELECT * FROM Task");
  QSqlQuery query(queryString);
  while (query.next()) {
    QString           id          = query.value("id").toString();
    QString           name        = query.value("name").toString();
    QString           description = query.value("description").toString();
    QString           assignee    = query.value("assignee").toString();
    int               progress    = -1;
    // TaskEnums::TaskType progress
    // =static_cast<TaskEnums::TaskType>(query.value("progress").toInt());
    TaskEnums::Status status =
        static_cast<TaskEnums::Status>(query.value("status").toInt());
    TaskEnums::Priority priority =
        static_cast<TaskEnums::Priority>(query.value("priority").toInt());
    TaskEnums::TaskType taskType =
        static_cast<TaskEnums::TaskType>(query.value("taskType").toInt());

    // 现在taskType变量包含了对应的枚举值，可以用于后续逻辑
    QString createdDate = query.value("createdDate").toString();
    QString startDate   = query.value("startDate").toString();
    QString endDate     = query.value("endDate").toString();
    QString reminders   = query.value("reminders").toString();

    qDebug() << "任务ID：" << id;
    qDebug() << "任务名称：" << name;
    qDebug() << "任务描述：" << description;
    qDebug() << "任务分配给：" << assignee;
    qDebug() << "任务进度：" << progress;
    qDebug() << "任务状态：" << status;
    qDebug() << "任务优先级：" << priority;
    qDebug() << "任务类型：" << taskType;
    qDebug() << "任务创建日期：" << createdDate;
    qDebug() << "任务开始日期：" << startDate;
    qDebug() << "任务结束日期：" << endDate;
    qDebug() << "任务提醒：" << reminders;
    TaskData e = TaskData{
        .id              = static_cast<unsigned int>(id.toInt()),
        .title           = name,
        .content         = description,
        .assignee        = assignee,
        .progress        = progress,
        .status          = status,
        .priority        = priority,
        .taskType        = taskType,
        .createdDateTime = TaskData::QStringtoQDateTime(createdDate),
        .startDateTime   = TaskData::QStringtoQDateTime(startDate),
        .completedTime   = TaskData::QStringtoQDateTime(endDate),
        .reminderTime    = TaskData::QStringtoQDateTime(reminders),
    };
  }
  return taskList;
}
// 对大量数据进行快速添加，尝试过添加几千条数据，不到一秒就添加完成
bool TaskDB::FastAdd() {
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
  return true;
}
