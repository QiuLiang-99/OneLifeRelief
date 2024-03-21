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
  target->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch); // 自动设置列宽

  QStringList timingofClass;
  QTime C1(8, 0), C2(8, 55), C3(9, 55), C4(10, 50), C5(11, 45), C6(14, 30),
      C7(15, 25), C8(16, 25), C9(17, 20), C10(19, 00), C11(19, 50), C12(20, 40);
  timingofClass << "1\n" + C1.toString("hh:mm") << "2\n" + C2.toString("hh:mm")
                << "3\n" + C3.toString("hh:mm") << "4\n" + C4.toString("hh:mm")
                << "5\n" + C5.toString("hh:mm") << "6\n" + C6.toString("hh:mm")
                << "7\n" + C7.toString("hh:mm") << "8\n" + C8.toString("hh:mm")
                << "9\n" + C9.toString("hh:mm")
                << "10\n" + C10.toString("hh:mm")
                << "11\n" + C11.toString("hh:mm")
                << "12\n" + C12.toString("hh:mm");
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
  // TEST
  /*modelData = QList<lessonlItem>{
      {"aa", 1, 20, 90, 2},
      {"bb", 1, 23, 91, 2},
      {"cc", 0, 21, 95, 2},
  };*/
  // lessonlItem test = {"11111", "1", "1", "1", "1"};
  // modelData.append(test);
}
int ScheduleModel::rowCount(const QModelIndex&) const {
  return modelData.count();
}
int ScheduleModel::columnCount(const QModelIndex&) const {
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
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    qDebug() << modelData.at(0).classname;
    return modelData.at(0).classname;
  }

  return QVariant();
}
