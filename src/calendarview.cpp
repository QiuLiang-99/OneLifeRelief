#include "calendarview.h"
#include <qdatetime.h>
#include <qlist.h>
#include <qtreeview.h>
#include <qvariant.h>

TreeItem::TreeItem(QList<QVariant> data, TreeItem* parent) :
    m_itemData(data), m_parentItem(parent) {
}
void TreeItem::appendChild(TreeItem* child) {
  m_childItems.push_back(child); // 向节点添加一个子节点
}
TreeItem* TreeItem::child(
    int row) { // 检查目标是否合法然后返回此节点的目标子节点
  return row >= 0 && row < childCount() ? m_childItems.at(row) : nullptr;
}
int TreeItem::childCount() const { // 获取当前节点的子节点数量
  return int(m_childItems.size());
}
int TreeItem::row() const { // 如果父节点中的子节点等于当前节点就返回迭代器值
  if (m_parentItem == nullptr) return 0;
  const auto it = std::find_if(m_parentItem->m_childItems.cbegin(),
                               m_parentItem->m_childItems.cend(),
                               [this](const TreeItem* treeItem) {
                                 return treeItem == this;
                               });

  if (it != m_parentItem->m_childItems.cend()) // 计算it到first的距离
    return std::distance(m_parentItem->m_childItems.cbegin(), it);
  Q_ASSERT(false);                             // should not happen
  return -1;
}
int TreeItem::columnCount() const {
  return int(m_itemData.count());
}
QVariant TreeItem::data(int column) const {
  return m_itemData.value(column);
}
TreeItem* TreeItem::parentItem() {
  return m_parentItem;
}
//---------------------------------------------------------------------------------------

TreeModel::TreeModel(const QString& data, QObject* parent) :
    QAbstractItemModel(parent) {
  QList<QVariant> rootItemText;
  rootItemText << "名称"
               << "状态"
               << "类型"
               << "截止日期"
               << "紧要程度";
  rootItem          = new TreeItem(rootItemText);
  auto            n = data.split('-');
  QList<QVariant> modelData;
  for (auto& index : n) {
    modelData.append(index);
  }
  auto i = new TreeItem(modelData, rootItem); // todo
  rootItem->appendChild(i);
}
TreeModel::~TreeModel() = default;
QModelIndex TreeModel::index(int                row,
                             int                column,
                             const QModelIndex& parent) const {
  if (!hasIndex(row, column, parent)) return {};

  TreeItem* parentItem = parent.isValid() ?
                             static_cast<TreeItem*>(parent.internalPointer()) :
                             rootItem;

  if (auto* childItem = parentItem->child(row))
    return createIndex(row, column, childItem);
  return {};
}
QModelIndex TreeModel::parent(const QModelIndex& index) const {
  if (!index.isValid()) return {};

  auto*     childItem  = static_cast<TreeItem*>(index.internalPointer());
  TreeItem* parentItem = childItem->parentItem();

  return parentItem != rootItem ?
             createIndex(parentItem->row(), 0, parentItem) :
             QModelIndex{};
}
int TreeModel::rowCount(const QModelIndex& parent) const {
  if (parent.column() > 0) return 0;

  const TreeItem* parentItem =
      parent.isValid() ?
          static_cast<const TreeItem*>(parent.internalPointer()) :
          rootItem;

  return parentItem->childCount();
}
int TreeModel::columnCount(const QModelIndex& parent) const {
  if (parent.isValid())
    return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  return rootItem->columnCount();
}
QVariant TreeModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole) return {};

  const auto* item = static_cast<const TreeItem*>(index.internalPointer());
  return item->data(index.column());
}
Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const {
  return index.isValid() ? QAbstractItemModel::flags(index) :
                           Qt::ItemFlags(Qt::NoItemFlags);
}
QVariant TreeModel::headerData(int             section,
                               Qt::Orientation orientation,
                               int             role) const {
  return orientation == Qt::Horizontal && role == Qt::DisplayRole ?
             rootItem->data(section) :
             QVariant{};
}
//---------------------------------------------------------------------------------------
calendarView::calendarView(QWidget* parent) : QTreeView(parent) {
  taskandGoalModel = new TreeModel("任务"); // todo
  setModel(taskandGoalModel);
}
