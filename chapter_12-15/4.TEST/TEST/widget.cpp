#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    Px = 200;
    Py = 200;

    ui->setupUi(this);
    ui->frame->installEventFilter(this);        //安装事件过滤器到窗口

    timer = new QTimer;             //定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(Set_Data()));//定时器槽函数
    timer->start(1000);             //定时器定时时间
}

Widget::~Widget()
{
    delete ui;
}

//事件过滤器
bool Widget::eventFilter(QObject *watched, QEvent *event){
    if(watched == ui->frame && event->type() == QEvent::Paint){//在frame上画图
        Painter();
    }else{}
    return QWidget::eventFilter(watched,event);     //将事件传递给父类
}

//绘图
void Widget::Painter(){
    QPainter p(ui->frame);              //在frame(框架上画图)
    QPen P;
    P.setWidth(2);                      //设置画笔宽度
    P.setColor(Qt::black);              //设置画笔颜色
    P.setStyle(Qt::DashLine);           //设置画笔风格
    p.setPen(P);                        //调用画笔

    p.drawEllipse(QPoint(Px,Py),20,20); //画目标圆

    p.drawLine(200,0,200,400);      //画横线
    p.drawLine(0,200,400,200);      //画竖线
}

//中心坐标设置
void Widget::Set_Data(){
    int Temp1,Temp2;
    Temp1 = qrand()%200;        //随机数
    Temp2 = qrand()%200;
    Px =  Temp1;                //X坐标
    Py =  Temp2;                //Y坐标
    update();
    qDebug() << Px << "\t" << Py;
}
