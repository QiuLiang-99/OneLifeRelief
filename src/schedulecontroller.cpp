#include "schedulecontroller.h"
#include <QDatetime>
#include <QFileDialog>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QString>
#include <array>
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qdebug.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qlist.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qwindowdefs_win.h>

Schedulecontroller::Schedulecontroller(QTableView* object) : target(object) {
  lessonModel = new ScheduleModel(target);
  target->setModel(lessonModel);

  QStringList weeksName;
  weeksName << "星期一"
            << "星期二"
            << "星期三"
            << "星期四"
            << "星期五"
            << "星期六"
            << "星期天";
  // TEST
  setHorizontalHead(weeksName);
  QStringList           timingofClass;
  std::array<QTime, 12> timeofLesson = {
      QTime(8, 0),   QTime(8, 55),  QTime(9, 55),  QTime(10, 50),
      QTime(11, 45), QTime(14, 30), QTime(15, 25), QTime(16, 25),
      QTime(17, 20), QTime(19, 00), QTime(19, 50), QTime(20, 40)};
  auto DtoS = [&](QTime t, QTime e = QTime(0, 45)) {
    QTime N(0, 0);
    QTime i = t.addSecs(N.secsTo(e));
    return t.toString("hh:mm") + "~" + i.toString("hh:mm");
  };
  for (int i = 0; i < timeofLesson.size();) {
    int t = i + 1;
    timingofClass << QString::number(t) + "\n" + DtoS(timeofLesson.at(i++));
  };
  setVerticalHead(timingofClass);
  target->verticalHeader()->setDefaultSectionSize(50);
  // target->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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
  QHeaderView*        header = new QHeaderView(Qt::Horizontal);
  QStandardItemModel* model  = new QStandardItemModel;
  model->setHorizontalHeaderLabels(labels);
  header->setModel(model);
  target->setHorizontalHeader(header);
  // target->setHorizontalHeaderLabels
}

void Schedulecontroller::setVerticalHead(const QStringList& labels) {
  QHeaderView*        header = new QHeaderView(Qt::Vertical);
  QStandardItemModel* model  = new QStandardItemModel;
  model->setVerticalHeaderLabels(labels);
  header->setModel(model);
  header->setSectionResizeMode(
      QHeaderView::Stretch); // 自动设置列宽,自动占满框体
  target->setVerticalHeader(header);
}
QString Schedulecontroller::openLessonjsonPath() {
  // 定义文件对话框类
  QFileDialog* fileDialog = new QFileDialog(nullptr);
  // 定义文件对话框标题
  fileDialog->setWindowTitle(QStringLiteral("选择课表json文件"));
  // 设置打开的文件路径
  fileDialog->setDirectory("");
  // 设置文件过滤器,只显示.ui .cpp 文件,多个过滤文件使用空格隔开
  fileDialog->setNameFilter("*.json");
  // 设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
  fileDialog->setFileMode(QFileDialog::ExistingFiles);
  // 设置视图模式
  fileDialog->setViewMode(QFileDialog::Detail);
  // 获取选择的文件的路径
  QStringList fileNames;
  if (fileDialog->exec()) {
    fileNames = fileDialog->selectedFiles();
  }
  return fileNames.at(0);
}

void Schedulecontroller::analysisjson(QString path) {
  QFile file(path);
  file.open(QIODevice::ReadOnly);
  QByteArray data = file.readAll();
  file.close();

  // 解析
  QJsonParseError parseError;
  QJsonDocument   doc = QJsonDocument::fromJson(data, &parseError);
  if (parseError.error != QJsonParseError::NoError) {
    qDebug() << "配置错误";
    return;
  }
  QJsonObject obj = doc.object();
  if (obj.contains("kbList")) {
    QJsonValue  arrayTemp = obj.value("kbList");
    QJsonArray  array     = arrayTemp.toArray();
    QStringList targetValue;
    targetValue << "cdmc" //"实A-206"
                << "jcor" //"3-5"
                << "kcmc" // Excel数据处理与应用
                << "xm" //"原冠秀"
                << "xqjmc" //"星期四"
                << "zcd"; //"1-17周(单)"
    auto OtoS = [&](const QJsonObject subObj, const QString& s) {
      return subObj.value(s).toString();
    };
    for (int i = 0, V = 0; i < array.size(); i++, V = 0) {
      QJsonValue         sub            = array.at(i);
      QJsonObject        subObj         = sub.toObject();
      QString            loaction       = OtoS(subObj, targetValue.at(V++));
      QString            timeoflessonS  = OtoS(subObj, targetValue.at(V++));
      QString            classname      = OtoS(subObj, targetValue.at(V++));
      QString            teachername    = OtoS(subObj, targetValue.at(V++));
      QString            dayofweek      = OtoS(subObj, targetValue.at(V++));
      QString            weeks          = OtoS(subObj, targetValue.at(V++));
      QStringList        timeoflessonSL = timeoflessonS.split('-');
      std::array<int, 2> timeoflesson{timeoflessonSL.at(0).toInt(),
                                      timeoflessonSL.at(1).toInt()};
      qDebug() << timeoflesson.at(0) << timeoflesson.at(1);
      lessonlItem e = {loaction, classname, teachername, dayofweek, weeks};
      lessonModel->modelData.append(e);
    }
  } else {
    qDebug() << "课表为空";
  }
}

ScheduleModel::ScheduleModel(QObject* parent) : QAbstractTableModel(parent) {
}
int ScheduleModel::rowCount(const QModelIndex&) const {
  qDebug() << "rowCount" << modelData.count();
  return modelData.count();
}
int ScheduleModel::columnCount(const QModelIndex&) const {
  qDebug() << "columnCount";
  return 5;
}
QVariant ScheduleModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) return QVariant();
  /*if (role == Qt::DisplayRole || role == Qt::EditRole) {
    const int row = index.row();
    switch (index.column()) {
    case 0:
      return modelData.at(row).classname;
    case 1:
      return (modelData.at(row).teachername);
    case 2:
      return modelData.at(row).dayofweek;
    case 3:
      return modelData.at(row).weeks;
    }
  }*/
  auto dayofweek = [&](QString str) {
    auto StoI = [=](QString s) {
      if (s == "星期一") return 0;
      if (s == "星期二") return 1;
      if (s == "星期三") return 2;
      if (s == "星期四") return 3;
      if (s == "星期五") return 4;
      if (s == "星期六") return 5;
      if (s == "星期天") return 6;
      return -1;
    };
    return StoI(str) == index.column();
  };

  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    if (dayofweek(modelData.at(0).dayofweek)) {
    }
    qDebug() << modelData.at(0).classname;
    return modelData.at(0).classname;
  }

  return QVariant();
}
