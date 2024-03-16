#include "mianwidget.h"
#include "./ui_mianwidget.h"

MianWidget::MianWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MianWidget)
{
    ui->setupUi(this);

}

MianWidget::~MianWidget()
{
    delete ui;
}
