#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/CourseScheduleView.h"
#include <QLabel>
#include <QStackedWidget>
#include <QWidget>
#include <qboxlayout.h>
#include <qframe.h>
#include <qpushbutton.h>
#include <qsize.h>
#include <qwidget.h>

#include <QButtonGroup>

class MainWindow : public QWidget {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  public:
    void            setupUI();
    QGridLayout*    gridLayout;
    QVBoxLayout*    buttonlayout;
    QStackedWidget* mainWidget;
};

#endif // MAINWINDOW_H
