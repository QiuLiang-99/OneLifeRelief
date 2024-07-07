#include "taskdata.h"
QX_REGISTER_CPP_EXPORT_DLL(test)

namespace qx {
  template <>
  void register_class(QxClass<test>& t) {

    t.setName("User"); // 设置表名
    // 注册 User::id <=> 数据库中的主键
    t.id(&test::id, "id");
    // 注册 User::name 属性，使用的 key 是 name，version 是 1。
    t.data(&test::name, "name");
  }
} // namespace qx