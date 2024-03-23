#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include <QTreeView>
class TreeItem {
  public:
    explicit TreeItem(QList<QVariant> data, TreeItem* parentItem = nullptr);

    void appendChild(TreeItem* child);

    TreeItem* child(int row);
    int       childCount() const;
    int       columnCount() const;
    QVariant  data(int column) const;
    int       row() const;
    TreeItem* parentItem();

  private:
    std::vector<TreeItem*> m_childItems;
    QList<QVariant>        m_itemData;
    TreeItem*              m_parentItem;
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
class calendarView : public QTreeView {
  public:
    explicit calendarView(QWidget* parent = nullptr);

  private:
    TreeModel* taskandGoalModel;
};

#endif // CALENDARVIEW_H
