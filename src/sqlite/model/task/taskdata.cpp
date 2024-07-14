#include "taskdata.h"

QX_REGISTER_CPP_EXPORT_DLL(TaskData)

namespace qx {
  template <>
  void register_class(QxClass<TaskData>& t) {
    t.setSoftDelete(qx::QxSoftDelete("deleted_at"));
    t.setName("TaskData"); // 设置表名
    t.id(&TaskData::id, "id");

    t.data(&TaskData::title, "title");
    t.data(&TaskData::content, "content");
    t.data(&TaskData::assignee, "assignee");
    t.data(&TaskData::progress, "progress");
    t.data(&TaskData::status, "status");
    t.data(&TaskData::priority, "priority");
    t.data(&TaskData::taskType, "taskType");
    t.data(&TaskData::createdDateTime, "createdDateTime");
    t.data(&TaskData::startDateTime, "startDateTime");
    t.data(&TaskData::modifiedTime, "modifiedTime");
    t.data(&TaskData::completedTime, "completedTime");
    /*t.data(&TaskData::projectId, "projectId");
t.data(&TaskData::imgMode, "imgMode");
t.data(&TaskData::parentId, "parentId");
t.data(&TaskData::tags, "tags");
t.data(&TaskData::reminderTime, "reminderTime");
t.data(&TaskData::childrenString, "childrenString");*/

    // todo dao完善
  }
} // namespace qx