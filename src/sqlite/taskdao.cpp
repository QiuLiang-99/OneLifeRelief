#include "taskdao.h"
#include "model/task/taskdata.h"
#include "sqlite/taskdatabasecache.h"
#include <QxCommon/QxMacro.h>
#include <QxDao/QxDao.h>
#include <QxOrm.h>
#include <QxRegister/QxClass.h>
#include <QxRegister/QxRegister.h>
#include <qcontainerfwd.h>
#include <qlist.h>

TaskDAO::TaskDAO(TaskDatabaseCache& db, QObject* parent) :
    QObject(parent), DBcache(db) {
  qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
  qx::QxSqlDatabase::getSingleton()->setDatabaseName("sometest.db");
  qx::dao::create_table<TaskData>();
}
TaskDAO::~TaskDAO() {}

void TaskDAO::saveCachetoDatabase() {
  // bug 雪花id一存就不见了
  qx::dao::save(DBcache.data());
}
void TaskDAO::loadDatabaseintoCache() { qx::dao::fetch_all(DBcache.data()); }