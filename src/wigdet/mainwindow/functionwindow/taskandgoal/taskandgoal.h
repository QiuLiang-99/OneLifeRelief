#ifndef TASKANDGOAL_H
#define TASKANDGOAL_H
#include "sqlite/model/task/taskdata.h"
#include "src/include/QTUI.h"

class TreeItem {
    // AS a treeitem

  public:
    explicit TreeItem(QVector<QVariant> data, TreeItem* parentItem = nullptr);
    // explicit TreeItem(const TaskData& taskData, TreeItem* parentItem =
    // nullptr);
    ~TreeItem();
    void      appendChild(TreeItem* child);
    TreeItem* child(int row);
    int       childCount() const;
    int       columnCount() const;
    QVariant  data(int column) const;
    bool      setData(int column, const QVariant& value);
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
    bool          setData(const QModelIndex& index,
                          const QVariant&    value,
                          int                role = Qt::EditRole) override;
    /*The dataChanged() and
         headerDataChanged() signals must be emitted          explicitly when
       reimplementing the setData() and setHeaderData() functions,
       respectively.*/
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
    explicit taskandGoalWidget(QWidget* parent = nullptr);
};
#endif // TASKANDGOAL_H
