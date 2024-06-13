#ifndef TASKANDGOAL_H
#define TASKANDGOAL_H
#include "src/include/QTUI.h"

class TreeItem {
    // AS a treeitem

  public:
    explicit TreeItem(QVector<QVariant> data, TreeItem* parentItem = nullptr);
    ~TreeItem();
    void      appendChild(TreeItem* child);
    TreeItem* child(int row);
    int       childCount() const;
    int       columnCount() const;
    QVariant  data(int column) const;
    int       row() const;
    TreeItem* parent();

  private:
    QVector<TreeItem*> childItems;
    QVector<QVariant>  itemData;
    TreeItem*          parentItem;
};
class TreeModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    Q_DISABLE_COPY_MOVE(TreeModel)

    explicit TreeModel(const QString& data, QObject* parent = nullptr);
    ~TreeModel() override;

    QVariant      data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant      headerData(int             section,
                             Qt::Orientation orientation,
                             int             role = Qt::DisplayRole) const override;
    QModelIndex   index(int                row,
                        int                column,
                        const QModelIndex& parent = {}) const override;
    QModelIndex   parent(const QModelIndex& index) const override;
    int           rowCount(const QModelIndex& parent = {}) const override;
    int           columnCount(const QModelIndex& parent = {}) const override;

  private:
    TreeItem* rootItem;
};
class taskandGoalView : public QTreeView {
  public:
    explicit taskandGoalView(QWidget* parent = nullptr);

  private:
    TreeModel* taskandGoalModel;
};
class taskandGoalWidget : public QWidget {
    Q_OBJECT

  public:
    explicit taskandGoalWidget(QWidget* parent = nullptr) : QWidget(parent) {
      QVBoxLayout*     pageLayout = new QVBoxLayout(this);
      taskandGoalView* taskView   = new taskandGoalView;
      pageLayout->setSpacing(0); // 表示各个控件之间的上下间距
      pageLayout->setContentsMargins(0, 0, 0, 0);
      pageLayout->addWidget(taskView);
    };
    //~taskandGoalWidget();
};
#endif // TASKANDGOAL_H
