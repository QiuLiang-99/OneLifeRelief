#include "olrmainwindow.h"

OLRMainWindow::OLRMainWindow(QWidget* parent) : QWidget(parent) { setupUI(); }

OLRMainWindow::~OLRMainWindow() {}

void OLRMainWindow::setupUI() {
  // 初始化控件
  mainLayout    = new QVBoxLayout(this);
  contentLayout = new QHBoxLayout();
  leftLayout    = new QVBoxLayout();
  rightLayout   = new QVBoxLayout();

  // 左侧任务列表
  taskList      = new QListWidget(this);
  taskList->addItem("今天");
  taskList->addItem("最近7天");
  taskList->addItem("收集箱");
  leftLayout->addWidget(taskList);

  // 左侧类别列表
  categoryList = new QListWidget(this);
  categoryList->addItem("欢迎");
  categoryList->addItem("工作任务");
  categoryList->addItem("个人备忘");
  categoryList->addItem("购物清单");
  categoryList->addItem("心愿清单");
  categoryList->addItem("学习安排");
  categoryList->addItem("锻炼计划");
  categoryList->addItem("生日提醒");
  leftLayout->addWidget(categoryList);

  // 右侧任务详情
  taskDetailTree = new QTreeWidget(this);
  QStringList headers;
  headers << "任务名称"
          << "截止日期";
  taskDetailTree->setHeaderLabels(headers);
  QTreeWidgetItem* taskItem1 = new QTreeWidgetItem(taskDetailTree);
  taskItem1->setText(0, "45642123");
  taskItem1->setText(1, "5月21日");
  taskDetailTree->addTopLevelItem(taskItem1);

  QTreeWidgetItem* taskItem2 = new QTreeWidgetItem(taskDetailTree);
  taskItem2->setText(0, "3453543453213");
  taskItem2->setText(1, "5月21日");
  taskDetailTree->addTopLevelItem(taskItem2);

  rightLayout->addWidget(taskDetailTree);

  // 右侧任务详情标签
  taskDetailLabel = new QLabel("点击任务标签查看详情", this);
  taskDetailLabel->setAlignment(Qt::AlignCenter);
  rightLayout->addWidget(taskDetailLabel);

  // 将左右布局添加到内容布局
  contentLayout->addLayout(leftLayout);
  contentLayout->addLayout(rightLayout);

  // 将内容布局添加到主布局
  mainLayout->addLayout(contentLayout);

  // 设置主布局
  setLayout(mainLayout);
}
