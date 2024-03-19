#include "mianwidget.h"
#include "./ui_mianwidget.h"
#include "src/schedulecontroller.h"
#include <QFileDialog>

MianWidget::MianWidget(QWidget* parent) :
    QWidget(parent), ui(new Ui::MianWidget) {
  ui->setupUi(this);
  scheduler = new Schedulecontroller(ui->tableView_2);
  setWindowTitle("一身轻");
}

MianWidget::~MianWidget() {
  delete ui;
}

void MianWidget::on_pushButton_clicked() {
  ui->stackedWidget->setCurrentIndex(0);
}

void MianWidget::on_scheduleButton_clicked() {
  ui->stackedWidget->setCurrentIndex(1);
}

void MianWidget::on_importButton_clicked() {

  // 定义文件对话框类
  QFileDialog* fileDialog = new QFileDialog(this);

  // 定义文件对话框标题
  fileDialog->setWindowTitle(QStringLiteral("选择课表json文件"));

  // 设置打开的文件路径
  fileDialog->setDirectory("./");

  // 设置文件过滤器,只显示.ui .cpp 文件,多个过滤文件使用空格隔开
  fileDialog->setNameFilter(tr("File(*.json*)"));

  // 设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
  fileDialog->setFileMode(QFileDialog::ExistingFiles);

  // 设置视图模式
  fileDialog->setViewMode(QFileDialog::Detail);

  // 获取选择的文件的路径
  QStringList fileNames;

  if (fileDialog->exec()) {
    fileNames = fileDialog->selectedFiles();
    qDebug() << fileNames;
  }
}
