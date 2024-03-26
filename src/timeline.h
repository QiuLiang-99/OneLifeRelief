#ifndef TIMELINE_H
#define TIMELINE_H
#include <QWidget>
class Timeline : public QWidget {
    Q_OBJECT

  public:
    explicit Timeline(QWidget* parent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;

  signals:
};

#endif // TIMELINE_H
