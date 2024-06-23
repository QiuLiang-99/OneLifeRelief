#ifndef COURSESCHEDULE_H
#define COURSESCHEDULE_H
#include <QAbstractTableModel>
#include <QDateTime>
#include <QString> // Add this line to import the QString type
#include <QTableView>
#include <array>
#include <qboxlayout.h>
#include <qlist.h>
#include <qtableview.h>
#include <qwidget.h>

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
class CourseScheduleView : public QTableView {
  public:
    explicit CourseScheduleView(QWidget* parent = nullptr);
    void    setHorizontalHead(const QStringList&);
    void    setVerticalHead(const QStringList&);
    void    openCalendar(QDate);
    QString openLessonjsonPath();
    void    analysisjson(QString);

  private:
    ScheduleModel* lessonModel;
};

#endif // COURSESCHEDULE_H
