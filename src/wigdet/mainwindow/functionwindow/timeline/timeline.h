#ifndef TIMELINE_H
#define TIMELINE_H
#include "src/include/QTUI.h"
#include "src/wigdet/universalwigdet/newtask/newtask.h"

class Timeline : public QWidget {
    Q_OBJECT

  public:
    explicit Timeline(QWidget* parent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;

  signals:
};
class TimeLineWidget : public QWidget {
    Q_OBJECT

  public:
    explicit TimeLineWidget(QWidget* parent = nullptr) : QWidget(parent) {
      QVBoxLayout* pageLayout               = new QVBoxLayout(this);
      QScrollArea* scrollArea               = new QScrollArea;
      QWidget*     scrollAreaWidgetContents = new QWidget;
      QVBoxLayout* scorllAreaLayout         = new QVBoxLayout;
      Timeline*    timeLine                 = new Timeline;
      scrollArea->setWidget(scrollAreaWidgetContents);
      pageLayout->setSpacing(0); // 表示各个控件之间的上下间距
      pageLayout->setContentsMargins(0, 0, 0, 0);

      scrollAreaWidgetContents->setGeometry(0, 0, 5000, 100);
      scrollAreaWidgetContents->setLayout(scorllAreaLayout);

      scorllAreaLayout->addWidget(timeLine);

      pageLayout->addWidget(new AddTaskButton);
      pageLayout->addWidget(scrollArea);

      timeLine->setVisible(true);

      // connect(test, &QPushButton::clicked, this,
      // &MainWindow::on_test_clicked);
    };
    //~TimeLineWidget();
};
#endif // TIMELINE_H
