#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include <QTreeView>
#include <memory>
// person信息
typedef struct Person_t {
    QString name;  // 姓名
    QString sex;   // 性别
    int     age;   // 年龄
    QString phone; // 电话号码
    Person_t() {
      age = 0;
    }
} Person;

// 省份信息
typedef struct Province_t {
    QString          name;
    QVector<Person*> people;
} Province;
class TreeItem {
  public:
    explicit TreeItem(QVariantList data, TreeItem* parentItem = nullptr);

    void appendChild(std::unique_ptr<TreeItem>&& child);

    TreeItem* child(int row);
    int       childCount() const;
    int       columnCount() const;
    QVariant  data(int column) const;
    int       row() const;
    TreeItem* parentItem();

  private:
    std::vector<std::unique_ptr<TreeItem>> m_childItems;
    QVariantList                           m_itemData;
    TreeItem*                              m_parentItem;
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
    static void setupModelData(const QList<QStringView>& lines,
                               TreeItem*                 parent) {
      QVariantList list;
      for (const auto& part : lines) {
        QString temp(part.data(), static_cast<int>(part.size()));
        list.append(temp);
      }

      auto n = std::make_unique<TreeItem>(list, nullptr); // test
      parent->appendChild(std::move(n));
    };

    std::unique_ptr<TreeItem> rootItem;
};
class calendarView : public QTreeView {
  public:
    explicit calendarView(QWidget* parent = nullptr);

  private:
    TreeModel* taskandGoalModel;
};

#endif // CALENDARVIEW_H
