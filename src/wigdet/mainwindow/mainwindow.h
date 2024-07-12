#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/QTUI.h"
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

  public:
    void appendNewButton(const QString&);

  protected:
    void resizeEvent(QResizeEvent* event) override;

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
