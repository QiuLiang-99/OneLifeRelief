#ifndef NEWTASKWIDGET_H
#define NEWTASKWIDGET_H
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QDateEdit>
#include <QDialog>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
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

  private:
    QVBoxLayout* mainLayout;
    QLineEdit*   taskNameEdit;
    QTextEdit*   descriptionEdit;
    QHBoxLayout* buttonLayout;
    QPushButton* todayButton;
    QPushButton* priorityButton;
    QPushButton* remindButton;
    QPushButton* upgradeButton;
    QPushButton* moreButton;
    QHBoxLayout* inboxLayout;
    QLabel*      inboxLabel;
    QComboBox*   inboxComboBox;
    QHBoxLayout* actionLayout;
    QPushButton* cancelButton;
    QPushButton* addButton;
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
