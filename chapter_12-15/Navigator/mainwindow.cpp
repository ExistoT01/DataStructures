#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set location position
    this->locatePosition = {
        {330, 640},
        {340, 480},
        {290, 430},
        {260, 380},
        {210, 510},
        {370, 310},
        {160, 300},
        {120, 170},
        {120, 250},
        {240, 130},
        {380, 150},
        {550, 140}
    };

    // set size
    this->setFixedSize(1280, 720);

    // set pic&others
    picBox = new myLabel(this);
    picBox->setGeometry(30, 10, 620, 700);
    picBox->setStyleSheet("background-image: url(:/map_1.jpg);"
                          "border-radius: 10px;");
//    picBox->installEventFilter(this);
//    QPainter painter(picBox);
//    QPen P;
//    P.setWidth(6);                      //设置画笔宽度
//    P.setColor(Qt::red);              //设置画笔颜色
//    P.setStyle(Qt::DashLine);           //设置画笔风格
//    painter.setPen(P);                        //调用画笔

//    picBox->Paint();


    title = new QLabel(this);
    title->setGeometry(740, 40, 440, 200);
    title->setStyleSheet("background-image: url(:/title.jpg);"
                         " border-radius: 10px; ");

    sel_title_1 = new QLabel(this);
    sel_title_1->setGeometry(740, 280, 150, 50);
    sel_title_1->setStyleSheet("background-image: url(:/title_1.jpg);"
                               " border-radius: 10px; ");

    sel_title_2 = new QLabel(this);
    sel_title_2->setGeometry(1030, 280, 150, 50);
    sel_title_2->setStyleSheet("background-image: url(:/title_2.jpg);"
                               " border-radius: 10px; ");

    comboBox_1 = new QComboBox(this);
    comboBox_1->addItems(locateList);
    comboBox_1->setGeometry(740, 360, 150, 50);

    comboBox_2 = new QComboBox(this);
    comboBox_2->addItems(locateList);
    comboBox_2->setGeometry(1030, 360, 150, 50);

    sel_title_3 = new QLabel(this);
    sel_title_3->setGeometry(740, 440, 150, 50);
    sel_title_3->setStyleSheet("background-image: url(:/title_3.jpg);"
                               " border-radius: 10px; ");

    distanceBox = new QLabel(this);
    distanceBox->setGeometry(1030, 440, 150, 50);
    distanceBox->setStyleSheet("background-color: white;"
                               " border-radius: 10px; ");
    QFont font = distanceBox->font();
    font.setPointSize(18);
    font.setBold(true);
    distanceBox->setFont(font);
    distanceBox->setText("0");
    distanceBox->setAlignment(Qt::AlignCenter);

    sel_title_4 = new QLabel(this);
    sel_title_4->setGeometry(740, 520, 150, 50);
    sel_title_4->setStyleSheet("background-image: url(:/title_4.jpg);"
                               " border-radius: 10px; ");

    calcBtn = new QPushButton(this);
    calcBtn->setGeometry(1030, 520, 150, 50);
    calcBtn->setFont(font);
    calcBtn->setText("点击计算");
    connect(calcBtn, &QPushButton::clicked, this, &MainWindow::calcBtnClicked);

    pathBox = new QLabel(this);
    pathBox->setGeometry(740, 600, 440, 100);
    pathBox->setStyleSheet("background-color: white;"
                           " border-radius: 10px; ");
    pathBox->setWordWrap(true);
    QFont pathFont = pathBox->font();
    pathFont.setFamily("SimHei");
    pathFont.setPointSize(12);
    pathBox->setFont(pathFont);

//    setMouseTracking(true);



}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calcBtnClicked(){



    vector<int> pre;
    stack<int> stk;
    pre.resize(Dijkstra().n);
    int start = comboBox_1->currentIndex(), end = comboBox_2->currentIndex();
    int distance = Dijkstra().dij(start, end, pre);
    QString path = "";
    while (pre[end] != end) {
        stk.emplace(end);
        end = pre[end];
    }
    stk.emplace(end);
    pathStk = stk;

    while(!stk.empty()){
        path += locateList[stk.top()];
        if(stk.size() != 1){
            path +=  + " -> ";
        }
        stk.pop();

    }

//    qDebug() << "start: " << comboBox_1->currentText();
//    qDebug() << "startIndex: " << comboBox_1->currentIndex();
//    qDebug() << "end: " << comboBox_2->currentText();
//    qDebug() << "endIndex: " << comboBox_2->currentIndex();
//    qDebug() << "distance: " << distance;
//    qDebug() << "path: " << path;

    distanceBox->setText(QString::number(distance));
    pathBox->setText(path);

//    QPaintEvent* evt = new QPaintEvent(QRect(50, 50, 90, 90));
//    picBox->paintEvent(evt);

}

//事件过滤器
//bool MainWindow::eventFilter(QObject *watched, QEvent *event){
//    if(watched == picBox && event->type() == QEvent::Paint){//在frame上画图
//        Painter();
//    }else{}
//    return QWidget::eventFilter(watched,event);     //将事件传递给父类
//}

//void MainWindow::paintEvent(QPaintEvent *event){
//    QPainter p(picBox);              //在frame(框架上画图)
//    QPen P;
//    P.setWidth(6);                      //设置画笔宽度
//    P.setColor(Qt::red);              //设置画笔颜色
//    P.setStyle(Qt::DashLine);           //设置画笔风格
//    p.setPen(P);                        //调用画笔

////    qDebug() << event->rect();
//    p.drawLine(0, 0, 20, 20);
//}

//绘图
//void MainWindow::Painter(){
//    QPainter p(picBox);              //在frame(框架上画图)
//    QPen P;
//    P.setWidth(2);                      //设置画笔宽度
//    P.setColor(Qt::black);              //设置画笔颜色
//    P.setStyle(Qt::DashLine);           //设置画笔风格
//    p.setPen(P);                        //调用画笔

//    p.drawEllipse(QPoint(0,0),20,20); //画目标圆

//    p.drawLine(200,0,200,400);      //画横线
//    p.drawLine(0,200,400,200);      //画竖线





////    QPainter p(picBox);              //在frame(框架上画图)
////    QPen P;
////    P.setWidth(6);                      //设置画笔宽度
////    P.setColor(Qt::red);              //设置画笔颜色
////    P.setStyle(Qt::DashLine);           //设置画笔风格
////    p.setPen(P);                        //调用画笔

////    int x0 = 0, x1 = 0, y0 = 0, y1 = 0;
////    while(!pathStk.empty()){
////        x0 = locatePosition[pathStk.top()][0];
////        y0 = locatePosition[pathStk.top()][1];
////        x0 -= 30, x1 -= 30;

////        pathStk.pop();
////        if(!pathStk.empty()){
////            x1 = locatePosition[pathStk.top()][0];
////            y1 = locatePosition[pathStk.top()][1];
////            y0 -= 10, y1 -= 10;
////            p.drawLine(x0, y0, x1, y1);      //画横线
////        }
////    }

//}

