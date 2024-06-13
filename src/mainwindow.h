#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/module/courseschedule/courseschedulewidget.h"
#include "src/module/taskandgoal.h"
#include "src/module/timeline.h"
#include <QLabel>
#include <QStackedWidget>
#include <QWidget>
#include <qboxlayout.h>
#include <qframe.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qsize.h>
#include <qstackedlayout.h>
#include <qtmetamacros.h>
#include <qwidget.h>

#include <QButtonGroup>

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
