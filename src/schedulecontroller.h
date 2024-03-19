#ifndef SCHEDULECONTROLLER_H
#define SCHEDULECONTROLLER_H
#include <QAbstractTableModel>
#include <QDateTime>
#include <QTableView>
struct lessonlItem {
    QString loaction;
    QString classname;
    QString teachername;
    QString dayofweek;
    QString weeks;
};
class ScheduleModel : public QAbstractTableModel {
    Q_OBJECT

  public:
    QList<lessonlItem> modelData; // 数据存放处

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

  private:
    QTableView*    target;
    ScheduleModel* lessonModel;
};

#endif // SCHEDULECONTROLLER_H
