#ifndef CourseScheduleView_H
#define CourseScheduleView_H
#include "newtask.h"
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
class CourseScheduleWidget : public QWidget {
    Q_OBJECT

  public:
    explicit CourseScheduleWidget(QWidget* parent = nullptr) : QWidget(parent) {
      QVBoxLayout* pageLayout = new QVBoxLayout(this);
      pageLayout->setSpacing(0); // 表示各个控件之间的上下间距
      pageLayout->setContentsMargins(0, 0, 0, 0);
      QPushButton* importBtn = new QPushButton("导入");
      pageLayout->addWidget(importBtn);
      connect(importBtn, &QPushButton::clicked, this, [=]() {
        newTaskWidget* newTask = new newTaskWidget;
        newTask->show();
      });
      CourseScheduleView* ScheduleView = new CourseScheduleView(this);
      pageLayout->addWidget(ScheduleView);
    };
    //~CourseScheduleWidget();
};
#endif // CourseScheduleView_H
