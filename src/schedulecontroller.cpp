#include "schedulecontroller.h"
#include <QDatetime>
#include <QHeaderView>
#include <QStandardItemModel>
#include <qlogging.h>
#include <qnamespace.h>
Schedulecontroller::Schedulecontroller(QTableView* object) : target(object) {
  ScheduleModel* model = new ScheduleModel(target);
  target->setModel(model);

  QStringList test = {"111", "222"};
  // TEST
  setHorizontalHead(test);

  setVerticalHead(test);
}
/*void Schedulecontroller::openCalendar(QDate date) { //初始化日历 int year,
   week; week = date.weekNumber(&year); // 获取年份和周数 QString dateString =
   QString("%1年%2月 第%3周").arg(year).arg(date.month()).arg(week);
    //ui->datenow->setText(dateString);

    QStandardItemModel *model = new QStandardItemModel(2, 7, this); // 6 rows, 7
   columns
    //ui->taskCalendar->setModel(model);

    QStringList headers = {"星期一", "星期二", "星期三", "星期四", "星期五",
   "星期六", "星期日"}; QFont font; font.setBold(true); QBrush brush(Qt::red);

    for (int i = 0; i < headers.size(); ++i) {
    //QStandardItem *item = new QStandardItem(headers[i]);
    if (i >= 5) { // 周末
            item->setFont(font);
            item->setForeground(brush);
    }
    model->setHorizontalHeaderItem(i, item);
    }
    int dayOfWeek = date.dayOfWeek();
    // 计算当前日期是本周的第几天
    // 填充本周的日期
    for (int i = 0; i < 7; ++i) {
    QDate currentDate = date.addDays(i - dayOfWeek + 1);
    //QStandardItem *item;
    // 检查日期是否超过当前月份的天数
    QString inputdate(QString::number(currentDate.day()));
    if (currentDate == QDate::currentDate())//如果是今天就标注一下
    {
        inputdate += "（今天）";
    }
    item = new QStandardItem(inputdate);
    model->setItem(0, i, item);
    // 检查每个Data对象
    int row = 1;
    for (QVector<taskdata>::iterator it = taskqlist.begin(); it !=
   taskqlist.end(); ++it) { const taskdata &n = *it; if
   (isDateInRange(n.startdate, n.enddate, currentDate)) { QStandardItem
   *valueItem = new QStandardItem(n.taskname);
            //QTextDocument *doc = new QTextDocument();

            //doc->setHtml(QString::fromStdString(text));
            model->setItem(row, i,
   valueItem);//->setToolTip(QString(doc->toPlainText())); //
   在匹配的Data对象的下一行添加一个新项目 row++;
            }
    }*/

void Schedulecontroller::setHorizontalHead(const QStringList& labels) {
  // qDebug() << labels;
  //  target->setColumnCount(7);
  //  target->setHorizontalHeaderLabels(labels);

  QHeaderView*        header = new QHeaderView(Qt::Horizontal);
  QStandardItemModel* model  = new QStandardItemModel;

  // labels << QStringLiteral("姓名") << QStringLiteral("年级")<<
  // QStringLiteral("学号");
  model->setHorizontalHeaderLabels(labels);
  header->setModel(model);
  target->setHorizontalHeader(header);
  // target->setHorizontalHeaderLabels
}

void Schedulecontroller::setVerticalHead(const QStringList& labels) {
  // target->setVerticalHeaderLabels(labels);
  QHeaderView*        header = new QHeaderView(Qt::Vertical);
  QStandardItemModel* model  = new QStandardItemModel;
  // labels << QStringLiteral("姓名") << QStringLiteral("年级")<<
  // QStringLiteral("学号");
  model->setVerticalHeaderLabels(labels);
  header->setModel(model);
  target->setVerticalHeader(header);
}
void Schedulecontroller::openLessonjson() {
  // TODO
}

ScheduleModel::ScheduleModel(QObject* parent) : QAbstractTableModel(parent) {
  // TEST
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
