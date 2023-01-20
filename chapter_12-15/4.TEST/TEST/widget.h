#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>      //Qt窗口
#include <QEvent>       //事件
#include <random>       //随机数
#include <QDebug>       //在线调试
#include <QTimer>       //定时器
#include <QPainter>     //画图
#include <QPen>         //画笔


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    bool eventFilter(QObject *watched, QEvent *event);  //事件滤波器
    void Painter();     //画图

private slots:
     void Set_Data();   //设置图像中心点坐标

private:
    Ui::Widget *ui;
    QTimer *timer;
    int Px,Py;
};

#endif // WIDGET_H
