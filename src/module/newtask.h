#ifndef NEWTASK_H
#define NEWTASK_H
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
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <qabstractbutton.h>
#include <qabstractspinbox.h>
#include <qboxlayout.h>
#include <qdatetime.h>
#include <qicon.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qsize.h>

class newTaskWidget : public QDialog {
    Q_OBJECT

  public:
    explicit newTaskWidget(QWidget* parent = nullptr);

  protected:
    void resizeEvent(QResizeEvent* event);

  public:
    void onAddButtonClicked();
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
#include <QApplication>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QDate>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class CalendarWindow : public QWidget {
  public:
    CalendarWindow(QWidget* parent = nullptr);

  private:
    QVBoxLayout*     mainLayout;
    QHBoxLayout*     topLayout;
    QPushButton*     dateButton;
    QVBoxLayout*     quickSelectLayout;
    QPushButton*     tomorrowButton;
    QPushButton*     nextWeekendButton;
    QPushButton*     nextWeekButton;
    QPushButton*     noDateButton;
    QCalendarWidget* calendar;
    QHBoxLayout*     timeLayout;
    QPushButton*     timeButton;
};

#endif // NEWTASK_H
