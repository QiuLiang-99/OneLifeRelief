#ifndef COMMONHELPER_H
#define COMMONHELPER_H
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QFile>
#include <QJsonArray>


class CommonHelper {
  public:
    static void setStyle(const QString& style) {
      QFile qss(style);
      qss.open(QFile::ReadOnly);
      qApp->setStyleSheet(qss.readAll());
      qss.close();
    }
    static void loadSchedule() {
      //读入所有内容
      QFile file("Schedule.json");
      file.open(QIODevice::ReadOnly);
      QByteArray data=file.readAll();
      file.close();

      //解析
      QJsonParseError parseError;
      QJsonDocument doc=QJsonDocument::fromJson(data,&parseError);
      if(parseError.error!=QJsonParseError::NoError){
        qDebug()<<"配置错误";
            return;
      }
      QJsonObject obj=doc.object();
      if(obj.contains("Student"))
      {
        QJsonValue arrayTemp=obj.value("Student");
        QJsonArray array=arrayTemp.toArray();
        QJsonValue sub=array.at(0);//因为里面就一个元素，如果有多个元素，可以通过array.size()遍历
        QJsonObject subObj=sub.toObject();
        //--------------
        QJsonValue idTemp=subObj.value("id");
        int id=idTemp.toInt();
        QJsonValue nameTemp=subObj.value("name");
        QString name=nameTemp.toString();
        QJsonValue genderTemp=subObj.value("gender");
        QString gender=genderTemp.toString();
      }

    }
    static void saveSchedule(){
      QJsonObject obj;
      QJsonArray array;
      QJsonObject sub;
      int id=01;
      QString name="zhangsan";
      QString gender="Male";
      sub.insert("id",QJsonValue(id));
      sub.insert("name",QJsonValue(name));
      sub.insert("gender",QJsonValue(gender));
      array.append(QJsonValue(sub));
      obj.insert("Student",QJsonValue(array));

      //写入到文件，名字为info.json
      QJsonDocument doc(obj);
      QByteArray data=doc.toJson();
      QFile file("Schedule.json");
      bool ok=file.open(QIODevice::WriteOnly);
                if(ok)
      {
        file.write(data);
                  qDebug()<<"write ok!";
        file.close();
      }
      else
      {
        qDebug()<<"write error!";
      }

    }
};
#endif // COMMONHELPER_H
