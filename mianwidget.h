#ifndef MIANWIDGET_H
#define MIANWIDGET_H

#include "src/schedulecontroller.h"
// #include <QTableWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MianWidget;
}
QT_END_NAMESPACE

class MianWidget : public QWidget {
  Q_OBJECT

public:
  MianWidget(QWidget *parent = nullptr);
  ~MianWidget();

private:
  Ui::MianWidget *ui;
  //Schedulecontroller scheduler;
};
#endif // MIANWIDGET_H
