#include "taskdata.h"

QX_REGISTER_CPP_EXPORT_DLL(TaskData)

namespace qx {
  template <>
  void register_class(QxClass<TaskData>& t) {

    t.setName("TaskData"); // 设置表名
    t.id(&TaskData::id, "id");
    t.data(&TaskData::title, "title");
    t.data(&TaskData::content, "content");
    // todo dao完善
  }
} // namespace qx