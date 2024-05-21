#include "task.h"
#include <QDebug>
#include <QUuid>

QString generateUUID() {
  // QDateTime::currentMSecsSinceEpoch();
  return QUuid::createUuid().toString();
}

Task::Task() {
  // 生成 UUID
  id = generateUUID();
  qDebug() << "Generated UUID:" << id;
}
