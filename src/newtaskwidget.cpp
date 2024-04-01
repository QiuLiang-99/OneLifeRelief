#include "newtaskwidget.h"
#include <QLineEdit>
#include <qabstractspinbox.h>
#include <qboxlayout.h>
#include <qlineedit.h>

NewTaskwidget::NewTaskwidget(QWidget* parent) : QWidget(parent) {
  QVBoxLayout* layout   = new QVBoxLayout(this);
  QLineEdit*   nameline = new QLineEdit("test");
  layout->addWidget(nameline);
}
