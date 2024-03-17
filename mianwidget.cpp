#include "mianwidget.h"
#include "./ui_mianwidget.h"
#include "src/schedulecontroller.h"

MianWidget::MianWidget(QWidget* parent) :
    QWidget(parent), ui(new Ui::MianWidget) {
  ui->setupUi(this);
  Schedulecontroller scheduler(ui->tableWidget);
  setWindowTitle("一身轻");

}

MianWidget::~MianWidget() {
  delete ui;
}
