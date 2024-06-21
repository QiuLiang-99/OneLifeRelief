#ifndef OLRMAINWINDOW_H
#define OLRMAINWINDOW_H

#include "src/include/QTUI.h"

class OLRMainWindow : public QWidget {
    Q_OBJECT

  public:
    OLRMainWindow(QWidget* parent = nullptr);
    ~OLRMainWindow();

  private:
    void setupUI();

    // 控件声明
    QVBoxLayout* mainLayout;
    QHBoxLayout* contentLayout;

    // 左侧布局
    QVBoxLayout* leftLayout;
    QListWidget* taskList;
    QListWidget* categoryList;

    // 右侧布局
    QVBoxLayout* rightLayout;
    QTreeWidget* taskDetailTree;
    QLabel*      taskDetailLabel;
};

#endif // OLRMAINWINDOW_H
