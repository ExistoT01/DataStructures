#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = 0);
    void Paint();
    void paintEvent(QPaintEvent *); // 重写绘图事件

};

#endif // MYLABEL_H
