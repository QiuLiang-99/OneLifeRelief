#include "taskandgoal.h"
#include <algorithm>

TreeItem::TreeItem(QVector<QVariant> data, TreeItem* parent) :
    itemData(std::move(data)), parentItem(parent) {}

TreeItem::~TreeItem() {
  qDeleteAll(childItems); // 删除所有子节点
}
void TreeItem::appendChild(TreeItem* child) {
  childItems.push_back(child); // 向节点添加一个子节点
}
TreeItem* TreeItem::child(int row) {
  return row >= 0 && row < childCount() ?
             childItems.at(row) :
             nullptr; // 检查目标是否合法然后返回此节点的目标子节点
}
int TreeItem::childCount() const { // 获取当前节点的子节点数量
  return static_cast<int>(childItems.size());
}
int TreeItem::row() const { // 如果父节点中的子节点等于当前节点就返回迭代器值
  if (parentItem == nullptr) { return 0; }
  const auto it = std::find_if(parentItem->childItems.cbegin(),
                               parentItem->childItems.cend(),
                               [this](const TreeItem* treeItem) {
                                 return treeItem == this;
                               });

  if (it != parentItem->childItems.cend()) {
    return std::distance(parentItem->childItems.cbegin(), it);
  }                // 计算it到first的距离
  Q_ASSERT(false); // should not happen
  return -1;
}
int TreeItem::columnCount() const { return static_cast<int>(itemData.count()); }
QVariant TreeItem::data(int column) const { return itemData.value(column); }
bool     TreeItem::setData(int column, const QVariant& value) {
  if (column < 0 || column >= itemData.size()) { return false; }
  itemData[column] = value;
  return true;
}
TreeItem* TreeItem::parent() { return parentItem; }
//---------------------------------------------------------------------------------------

TreeModel::TreeModel(const QString& data, QObject* parent) :
    QAbstractItemModel(parent) {
  QList<QVariant> rootItemText;
  rootItemText << "标题" // todo
               << "状态"
               << "类型"
               << "标签"
               << "重复次数"
               << "截止日期"
               << "紧要程度"
               << "任务链接" // todo url 文件夹 exe
               << "完成度";
  rootItem          = new TreeItem(rootItemText);
  auto            n = data.split('-');
  QList<QVariant> modelData;
  for (auto& index : n) {
    modelData.append(index);
  }
  TreeItem* i = new TreeItem(modelData, rootItem); // test
  rootItem->appendChild(i);
}
TreeModel::~TreeModel() = default;
QModelIndex TreeModel::index(int                row,
                             int                column,
                             const QModelIndex& parent) const {
  if (!hasIndex(row, column, parent)) { return {}; }

  TreeItem* parentItem = parent.isValid() ?
                             static_cast<TreeItem*>(parent.internalPointer()) :
                             rootItem;

  if (auto* childItem = parentItem->child(row)) {
    return createIndex(row, column, childItem);
  }
  return {};
}
QModelIndex TreeModel::parent(const QModelIndex& index) const {
  if (!index.isValid()) { return {}; }

  auto*     childItem  = static_cast<TreeItem*>(index.internalPointer());
  TreeItem* parentItem = childItem->parent();

  return parentItem != rootItem ?
             createIndex(parentItem->row(), 0, parentItem) :
             QModelIndex{};
}
int TreeModel::rowCount(const QModelIndex& parent) const {
  if (parent.column() > 0) { return 0; }

  const TreeItem* parentItem =
      parent.isValid() ?
          static_cast<const TreeItem*>(parent.internalPointer()) :
          rootItem;

  return parentItem->childCount();
}
int TreeModel::columnCount(const QModelIndex& parent) const {
  if (parent.isValid()) {
    return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  }
  return rootItem->columnCount();
}
QVariant TreeModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole) { return {}; }

  const auto* item = static_cast<const TreeItem*>(index.internalPointer());
  return item->data(index.column());
}
bool TreeModel::setData(const QModelIndex& index,
                        const QVariant&    value,
                        int                role) {
  if (role != Qt::EditRole) { return false; }

  TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
  item->setData(index.column(), value);
  emit dataChanged(index, index, {role});
  return true;
}
Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const {
  if (!index.isValid()) { return Qt::ItemFlags(Qt::NoItemFlags); }
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  // todo感觉不可以从treevieww更改会更好，要不做成设置吧，单击动作是可更改或者不可以更改
  // 使用|添加可编辑属性
  // index使用flags函数检查是否有效，如果无效会返回空
}
QVariant TreeModel::headerData(int             section,
                               Qt::Orientation orientation,
                               int             role) const {
  return orientation == Qt::Horizontal && role == Qt::DisplayRole ?
             rootItem->data(section) :
             QVariant{};
}
//---------------------------------------------------------------------------------------
taskandGoalView::taskandGoalView(QWidget* parent) : QTreeView(parent) {
  taskandGoalModel = new TreeModel("任务"); // todo
  setModel(taskandGoalModel);
}
taskandGoalWidget::taskandGoalWidget(QWidget* parent) : QWidget(parent) {
  QVBoxLayout*     pageLayout = new QVBoxLayout(this);
  taskandGoalView* taskView   = new taskandGoalView;
  pageLayout->setSpacing(0); // 表示各个控件之间的上下间距
  pageLayout->setContentsMargins(0, 0, 0, 0);
  pageLayout->addWidget(taskView);
};