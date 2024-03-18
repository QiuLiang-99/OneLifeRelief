#include "mianwidget.h"
#include "./ui_mianwidget.h"
#include "src/schedulecontroller.h"

MianWidget::MianWidget(QWidget* parent) :
    QWidget(parent), ui(new Ui::MianWidget) {
  ui->setupUi(this);
  Schedulecontroller scheduler(ui->tableView);
  setWindowTitle("一身轻");
}

MianWidget::~MianWidget() {
  delete ui;
}

void MianWidget::on_pushButton_clicked() {
}

void MianWidget::on_scheduleButton_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
}

