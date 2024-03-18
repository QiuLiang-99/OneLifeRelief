#include "schedulecontroller.h"
#include <qdatetime.h>

Schedulecontroller::Schedulecontroller(QTableView* object) : target(object) {
  /*QDateTime   now = QDateTime::currentDateTime();
  QStringList oneweek;
  for (QDate today = now.date(), date_end = now.date().addDays(7);
       today < date_end; today = today.addDays(1)) {
    oneweek << today.toString("dd");
  }
  setHorizontalHead(oneweek);*/
  ScheduleModel* model = new ScheduleModel(target);
  target->setModel(model);
}

void Schedulecontroller::setHorizontalHead(const QStringList& labels) {
  qDebug() << labels;
  // target->setColumnCount(7);
  // target->setHorizontalHeaderLabels(labels);
}

void Schedulecontroller::setVerticalHead(const QStringList& labels) {
  // target->setVerticalHeaderLabels(labels);
}

ScheduleModel::ScheduleModel(QObject* parent) : QAbstractTableModel(parent) {
  modelData = QList<lessonlItem>{
      {"aa", 1, 20, 90},
      {"bb", 1, 23, 91},
      {"cc", 0, 21, 95},
  };
}
int ScheduleModel::rowCount(const QModelIndex&) const {
  return modelData.count();
}
int ScheduleModel::columnCount(const QModelIndex&) const {
  return 5;
}
QVariant ScheduleModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) return QVariant();
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    const int row = index.row();
    switch (index.column()) {
    case 0:
      return modelData.at(row).name;
    case 1:
      return (modelData.at(row).sex == 0) ? "woman" : "man";
    case 2:
      return modelData.at(row).age;
    case 3:
      return modelData.at(row).score;
    }
  }
  return QVariant();
}
