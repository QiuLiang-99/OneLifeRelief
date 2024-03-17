#ifndef SCHEDULECONTROLLER_H
#define SCHEDULECONTROLLER_H
#include <QDateTime>
#include <QTableWidget>

class Schedulecontroller {
  public:
    Schedulecontroller(QTableWidget*);
    void setHorizontalHead(const QStringList&);
    void setVerticalHead(const QStringList&);

  private:
    QTableWidget* target;
};

#endif // SCHEDULECONTROLLER_H
