#include "courseschedule.h"
#include <QDatetime>
#include <QFileDialog>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QString>
#include <array>
#include <qabstractbutton.h>
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qdebug.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qlist.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qwidget.h>
// #include <qwindowdefs_win.h>

ScheduleModel::ScheduleModel(QObject* parent) : QAbstractTableModel(parent) {}
int ScheduleModel::rowCount(const QModelIndex&) const {
  return ScheduleData.at(0).size();
}
int ScheduleModel::columnCount(const QModelIndex&) const {
  return ScheduleData.size();
}
QVariant ScheduleModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) return QVariant();
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    if (ScheduleData.at(index.column()).empty()) {
      return QVariant();
    }
    auto subData = ScheduleData.at(index.column());
    if (subData.at(index.row())) { // 如果目标数据为空则提前返回
      return QVariant();
    }
    auto    obj = subData.at(index.row());
    QString content; // todo
    content += obj.classname + "\n";
    content += obj.loaction;
    content += obj.teachername;
    return content;
  }

  return QVariant();
}

void ScheduleModel::analysislessonlItem(lessonlItem item) {
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
  int                column         = StoI(item.dayofweek);
  QStringList        timeoflessonSL = item.timeoflesson.split('-');
  std::array<int, 2> timeoflessonA{timeoflessonSL.at(0).toInt() - 1,
                                   timeoflessonSL.at(1).toInt() - 1};
  int                row    = timeoflessonA.at(0);
  ScheduleData[column][row] = item;
  // todo
  // 没找到合适的方法，想法中应该是课表变更之后，设置一次合并单元格，现在用分析json结束之后就合并，耦合性提高了
}
//---------------------------------------------------------------------------------------
CourseScheduleView::CourseScheduleView(QWidget* parent) : QTableView(parent) {
  lessonModel = new ScheduleModel(this);
  this->setModel(lessonModel);
  QStringList weeksName;
  weeksName << "星期一"
            << "星期二"
            << "星期三"
            << "星期四"
            << "星期五"
            << "星期六"
            << "星期天";
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
}
void CourseScheduleView::setHorizontalHead(
    const QStringList& labels) { // 水平表头
  QHeaderView*        header = new QHeaderView(Qt::Horizontal);
  QStandardItemModel* model  = new QStandardItemModel;
  header->setSectionResizeMode(
      QHeaderView::Stretch); // 自动设置列宽,自动占满框体
  model->setHorizontalHeaderLabels(labels);
  header->setModel(model);
  header->setDefaultAlignment(Qt::AlignCenter); // 设置水平表头文本居中显示
  this->setHorizontalHeader(header);
}

void CourseScheduleView::setVerticalHead(
    const QStringList& labels) { // 竖直表头
  QHeaderView*        header = new QHeaderView(Qt::Vertical);
  QStandardItemModel* model  = new QStandardItemModel;
  header->setDefaultSectionSize(50);
  header->setSectionResizeMode(QHeaderView::Fixed);
  model->setVerticalHeaderLabels(labels);
  header->setModel(model);
  header->setDefaultAlignment(Qt::AlignCenter); // 设置竖直表头文本居中显示
  this->setVerticalHeader(header);
}
QString CourseScheduleView::openLessonjsonPath() {
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

void CourseScheduleView::analysisjson(QString path) {

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
    QStringList jsonValue;
    jsonValue << "cdmc"  //"实A-206"
              << "jcor"  //"3-5"
              << "kcmc"  // Excel数据处理与应用
              << "xm"    //"原冠秀"
              << "xqjmc" //"星期四"
              << "zcd";  //"1-17周(单)"
    auto OtoS = [&](const QJsonObject subObj, const QString& s) {
      return subObj.value(s).toString();
    };
    for (int i = 0, V = 0; i < array.size(); i++, V = 0) {
      QJsonValue  sub          = array.at(i);
      QJsonObject subObj       = sub.toObject();
      QString     loaction     = OtoS(subObj, jsonValue.at(V++)); //"实A-206"
      QString     timeoflesson = OtoS(subObj, jsonValue.at(V++)); //"3-5"
      QString     classname    = OtoS(subObj, jsonValue.at(V++));
      // Excel数据处理与应用
      QString     teachername  = OtoS(subObj, jsonValue.at(V++)); //"原冠秀"
      QString     dayofweek    = OtoS(subObj, jsonValue.at(V++)); //"星期四"
      QString weeks = OtoS(subObj, jsonValue.at(V++)); // todo "1-17周(单)"
      lessonlItem e = {loaction,  classname, teachername,
                       dayofweek, weeks,     timeoflesson};
      lessonModel->analysislessonlItem(e);
      // 设置单元格合并
      QStringList        timeoflessonSL = timeoflesson.split('-');
      std::array<int, 2> timeoflessonA{timeoflessonSL.at(0).toInt() - 1,
                                       timeoflessonSL.at(1).toInt()};
      auto               StoI = [=](QString s) {
        if (s == "星期一") return 0;
        if (s == "星期二") return 1;
        if (s == "星期三") return 2;
        if (s == "星期四") return 3;
        if (s == "星期五") return 4;
        if (s == "星期六") return 5;
        if (s == "星期天") return 6;
        return -1;
      }; // todo 提前就可以解析一下json，不用解析两次
      this->setSpan(timeoflessonA.at(0), StoI(dayofweek),
                    timeoflessonA.at(1) - timeoflessonA.at(0), 1);
    }
  } else {
    qDebug() << "课表为空";
  }
}
