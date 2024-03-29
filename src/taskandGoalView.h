#ifndef taskandGoalView_H
#define taskandGoalView_H

#include <QTreeView>
#include <qdatetime.h>
enum class Priority { // todo 紧急 重要
  TOP,
  HIGH,
  LOWER,
  WAIT
};
// book sport
enum class TaskType {
  Notype,
  STUDY,            // 学习
  WORK,             // 工作
  EXAM,             // 考试
  HABIT,            // 习惯
  CINEMA,           // 电影
  TRIP,             // 旅游
};
enum class Status { /*name inside outside*/
  NoStatus,
  Backlog,          // This item hasn't been started #DAFBE1 #1F883D
  Ready,            // This is ready to be picked up #DDF4FF #0969DA
  InProgress,       // This is actively being worked on #FFF8C5 #9A6700
  Inreview,         // This item is in review  #FBEFFF #8250DF
  Done,             // This has been completed #FFF1E5 #BC4C00
  Todo,             // #DAFBE1 #1F883D
  NotPlanned,       // This is not planned currently #FFEFF7 #BF3989
};
class TreeItem {
    // AS a treeitem

  public:
    explicit TreeItem(QVector<QVariant> data, TreeItem* parentItem = nullptr);
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

#endif // taskandGoalView_H
