#ifndef NEWTASKWIDGET_H
#define NEWTASKWIDGET_H
#include <QCoreApplication>
#include <QDialog>
#include <QFile>
#include <QPainter>
#include <QWidget>
#include <qabstractbutton.h>
#include <qdatetime.h>
#include <qicon.h>
#include <qpushbutton.h>
#include <qsize.h>

class newTaskWidget : public QDialog {
    Q_OBJECT

  public:
    explicit newTaskWidget(QWidget* parent = nullptr);

  protected:
    void resizeEvent(QResizeEvent* event);

  signals:
};
class AddTaskButton : public QPushButton {
    Q_OBJECT

  public:
    explicit AddTaskButton(QWidget* parent = nullptr) : QPushButton(parent) {
      QPixmap iconmap;
      iconmap.load("../OneLifeRelief/resource/icon/addbutton.jpg");
      QIcon icon(iconmap);
      this->setIcon(icon);
      this->setMinimumSize(50, 50);
      connect(this, &QPushButton::clicked, this, [&] {
        taskwidget = new newTaskWidget;
        taskwidget->show();
      });
    };

    // void paintEvent(QPaintEvent* event) override {}

  private:
    newTaskWidget* taskwidget;
};

#endif // NEWTASKWIDGET_H
