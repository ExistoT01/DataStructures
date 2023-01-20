#include "mylabel.h"

#include <QPainter>
myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
}
// 在控件发⽣重绘时触发的事件
void myLabel::paintEvent(QPaintEvent *)
{
    // 创建⼀个绘图对象，指定绘图设备为 QLabel
    QPainter painter(this);
    // 绘制⼀个图像
    painter.drawLine(0, 0, 100, 100);
    painter.end();
}

void myLabel::Paint(){
    QPainter p(this);              //在frame(框架上画图)
    QPen P;
    P.setWidth(2);                      //设置画笔宽度
    P.setColor(Qt::black);              //设置画笔颜色
    P.setStyle(Qt::DashLine);           //设置画笔风格
    p.setPen(P);                        //调用画笔

    p.drawEllipse(QPoint(0,0),20,20); //画目标圆

    p.drawLine(200,0,200,400);      //画横线
    p.drawLine(0,200,400,200);      //画竖线
}
