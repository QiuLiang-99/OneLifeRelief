#include "newtaskwidget.h"
#include <QLineEdit>
#include <qabstractspinbox.h>
#include <qboxlayout.h>
#include <qlineedit.h>

NewTaskWidget::NewTaskWidget(QWidget* parent) : QDialog(parent) {
  setWindowModality(Qt::WindowModal);
  QVBoxLayout* layout   = new QVBoxLayout(this);
  QLineEdit*   nameline = new QLineEdit("任务名称");
  layout->addWidget(nameline);
}
