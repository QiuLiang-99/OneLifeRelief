#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/wigdet/mainwindow/functionwindow/taskandgoal/taskandgoal.h"
#include "src/wigdet/mainwindow/functionwindow/timeline/timeline.h"
// #include "src/module/olrmainwindow/olrmainwindow.h"
#include "src/wigdet/mainwindow/functionwindow/courseschedule/courseschedulewidget.h"
// #include "src/wigdet/mainwindow/functionwindow/setting/setting.h"
#include "src/wigdet/mainwindow//olrmainwindow.h"

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
