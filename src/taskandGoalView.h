#ifndef taskandGoalView_H
#define taskandGoalView_H

#include <QTreeView>
#include <qdatetime.h>
enum Priority {
  TOP,
  HIGH,
  LOWER,
  WAIT
};
// book sport
enum TaskType {
  STUDY,  // 学习
  WORK,   // 工作
  EXAM,   // 考试
  HABIT,  // 习惯
  CINEMA, // 电影
  TRIP,   // 旅游
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

    // As data storage

  private:
    QString   name;
    QString   description;
    QDate     createdTime;
    QDate     startTime;
    QDate     endTime;
    bool      isCompleted;
    Priority  priority;
    TaskType  taskType;
    // todo 标签功能
    QDateTime reminders;
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
