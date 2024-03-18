#ifndef SCHEDULECONTROLLER_H
#define SCHEDULECONTROLLER_H
#include <QAbstractTableModel>
#include <QDateTime>
#include <QTableView>
class ScheduleModel : public QAbstractTableModel {
    Q_OBJECT
    struct lessonlItem {
        QString name;
        int     sex;
        int     age;
        int     score;
    };

    QList<lessonlItem> modelData;

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
    void setHorizontalHead(const QStringList&);
    void setVerticalHead(const QStringList&);
    void setModel(ScheduleModel*);

  private:
    QTableView* target;
};

#endif // SCHEDULECONTROLLER_H
