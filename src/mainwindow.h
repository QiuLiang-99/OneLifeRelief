#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/module/courseschedule/courseschedulewidget.h"
#include "src/module/newtask.h"
#include "src/module/olrmainwindow/olrmainwindow.h"
#include "src/module/taskandgoal.h"
#include "src/module/timeline.h"

class MainWindow : public QWidget {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  public:
    void appendNewButton(const QString&);

  protected:
    virtual void resizeEvent(QResizeEvent* event) override;

  public:
    void setupUI();

  public:
    QGridLayout*    gridLayout;
    QStackedLayout* mainWidget;
    QButtonGroup*   tablebtnGroup;

    QHBoxLayout* btnHLayout;
    QVBoxLayout* btnVLayout;
  private slots:
    void on_test_clicked();
};

#endif // MAINWINDOW_H
