#ifndef NEWTASK_H
#define NEWTASK_H
#include "src/include/QTUI.h"

class CalendarWindow : public QWidget {
  public:
    explicit CalendarWindow(QWidget* parent = nullptr);

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

class PriorityButton : public QPushButton {
    Q_OBJECT

  public:
    explicit PriorityButton(QWidget* parent = nullptr);

  private:
    void setupMenu();

    QMenu*   priorityMenu;
    QAction* priority1Action;
    QAction* priority2Action;
    QAction* priority3Action;
    QAction* priority4Action;
};
class newTaskWidget : public QDialog {
    Q_OBJECT

  public:
    explicit newTaskWidget(QWidget* parent = nullptr);

  protected:
    void resizeEvent(QResizeEvent* event);

  private slots:
    void onAddButtonClicked();
    void onTodayButtonClicked();
    void onPriorityButtonClicked();
    void onRemindButtonClicked();
    void onUpgradeButtonClicked();
    void onMoreButtonClicked();
    void onCancelButtonClicked();
    void checkTaskNameInput();
  signals:

  private:
    QVBoxLayout*    mainLayout;
    QLineEdit*      taskNameEdit;
    QTextEdit*      descriptionEdit;
    QHBoxLayout*    buttonLayout;
    QPushButton*    todayButton;
    QPushButton*    priorityButton;
    QPushButton*    remindButton;
    QPushButton*    upgradeButton;
    QPushButton*    moreButton;
    QHBoxLayout*    inboxLayout;
    QLabel*         inboxLabel;
    QComboBox*      inboxComboBox;
    QHBoxLayout*    actionLayout;
    QPushButton*    cancelButton;
    QPushButton*    addButton;
    CalendarWindow* calendarWindow;
};
class AddTaskButton : public QPushButton {
    Q_OBJECT

  public:
    explicit AddTaskButton(QWidget* parent = nullptr);

  private:
    newTaskWidget* taskwidget;
};
#endif // NEWTASK_H
