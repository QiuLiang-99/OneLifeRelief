#ifndef NEWTASK_H
#define NEWTASK_H
#include "src/include/QTUI.h"
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
