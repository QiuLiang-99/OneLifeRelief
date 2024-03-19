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
  scheduler->analysisjson(scheduler->openLessonjsonPath());
}
