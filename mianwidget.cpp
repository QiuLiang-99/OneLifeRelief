#include "mianwidget.h"
#include "./ui_mianwidget.h"
#include "src/CourseScheduleView.h"
#include <QFileDialog>

MianWidget::MianWidget(QWidget* parent) :
    QWidget(parent), ui(new Ui::MianWidget) {
  ui->setupUi(this);
  ScheduleView = new CourseScheduleView(ui->page_2);
  ui->gridLayout_2->addWidget(ScheduleView);
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
  ScheduleView->analysisjson(ScheduleView->openLessonjsonPath());
}
