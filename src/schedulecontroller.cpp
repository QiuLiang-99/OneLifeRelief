#include "schedulecontroller.h"
#include <qdatetime.h>

Schedulecontroller::Schedulecontroller(QTableWidget* object) : target(object) {
  QDateTime   now = QDateTime::currentDateTime();
  QStringList oneweek;
  for (QDate today = now.date(), date_end = now.date().addDays(7);
       today < date_end; today = today.addDays(1)) {
    oneweek << today.toString("dd");

  }

  setHorizontalHead(oneweek);
}

void Schedulecontroller::setHorizontalHead(const QStringList& labels) {
  qDebug()<< labels;
  target->setColumnCount(7);
  target->setHorizontalHeaderLabels(labels);
}

void Schedulecontroller::setVerticalHead(const QStringList& labels) {
  target->setVerticalHeaderLabels(labels);
}
