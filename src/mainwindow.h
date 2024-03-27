#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QStackedWidget>
#include <QWidget>
#include <qboxlayout.h>
#include <qframe.h>
#include <qpushbutton.h>
#include <qsize.h>
#include <qtmetamacros.h>
#include <qwidget.h>

#include <QButtonGroup>

class MainWindow : public QWidget {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  protected:
    virtual void resizeEvent(QResizeEvent* event) override;

  public:
    void            setupUI();
    QGridLayout*    gridLayout;
    QGridLayout*    buttonlayout;
    QStackedWidget* mainWidget;
  private slots:
    void on_test_clicked();
};

#endif // MAINWINDOW_H
