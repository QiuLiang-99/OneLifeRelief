#include "timeline.h"
#include <QPainter>
#include <QPen>
Timeline::Timeline(QWidget* parent) : QWidget(parent) {
}

void Timeline::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);        // 忽略未使用的参数警告

  QPainter painter(this); // 创建一个绘制器，指定绘制在当前小部件上

  // 设置画笔和字体
  painter.setPen(QPen(Qt::black)); // 设置画笔颜色为黑色
  QFont font = painter.font();     // 获取当前字体
  font.setPixelSize(12);           // 设置字体大小为 12 像素
  painter.setFont(font);           // 应用修改后的字体设置

  // 定义时间轴的起始位置和长度
  int startX = 50;           // 时间轴线的起始 x 坐标
  int endX   = width() - 50; // 时间轴线的结束 x 坐标
  int startY = height() / 2; // 时间轴线的 y 坐标（位于小部件高度的一半位置）

  // 绘制时间轴线
  painter.drawLine(startX, startY, endX, startY); // 画一条水平线，代表时间轴

  // 绘制刻度
  int interval = 50; // 刻度间隔
  for (int x = startX; x <= endX;
       x += interval) { // 从起始 x 坐标开始，每隔 interval 绘制一个刻度
    painter.drawLine(x, startY - 5, x, startY + 5); // 绘制一个垂直的刻度线
    painter.drawText(
        x - 10, startY + 20,
        QString::number((x - startX) / interval)); // 在刻度位置绘制刻度值
  }
}