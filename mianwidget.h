#ifndef MIANWIDGET_H
#define MIANWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MianWidget;
}
QT_END_NAMESPACE

class MianWidget : public QWidget
{
    Q_OBJECT

public:
    MianWidget(QWidget *parent = nullptr);
    ~MianWidget();

private:
    Ui::MianWidget *ui;
};
#endif // MIANWIDGET_H
