#ifndef SCHEDULECONTROLLER_H
#define SCHEDULECONTROLLER_H
#include <QAbstractTableModel>
#include <QDateTime>
#include <QTableView>
#include <array>
#include <qlist.h>
struct lessonlItem {
    QString loaction     = "";
    QString classname    = "";
    QString teachername  = "";
    QString dayofweek    = "";
    QString weeks        = "";
    QString timeoflesson = "";
    operator bool() const {
      return loaction.isEmpty() || classname.isEmpty() ||
             teachername.isEmpty() || dayofweek.isEmpty() || weeks.isEmpty() ||
             timeoflesson.isEmpty();
    }
};
class ScheduleModel : public QAbstractTableModel {
    Q_OBJECT

  public:
    std::array<std::array<lessonlItem, 12>, 7> ScheduleData;

  public:
    void analysislessonlItem(lessonlItem);

  public:
    explicit ScheduleModel(QObject* parent = nullptr);
    virtual int rowCount(
        const QModelIndex& = QModelIndex()) const override; // 目标行数
    virtual int columnCount(
        const QModelIndex& = QModelIndex()) const override; // 目标列数
    virtual QVariant data(const QModelIndex& index,
                          int role = Qt::DisplayRole) const override;
};
class Schedulecontroller {
  public:
    Schedulecontroller(QTableView*);
    void    setHorizontalHead(const QStringList&);
    void    setVerticalHead(const QStringList&);
    void    setModel(ScheduleModel*);
    void    openCalendar(QDate);
    QString openLessonjsonPath();
    void    analysisjson(QString);
    void    setSpan(int, int, int, int);

  private:
    QTableView*    target;
    ScheduleModel* lessonModel;
};

#endif // SCHEDULECONTROLLER_H
