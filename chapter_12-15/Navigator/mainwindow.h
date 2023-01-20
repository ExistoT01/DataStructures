#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QDebug>
#include <QPen>
#include <QMouseEvent>
#include <QPainter>
#include "dijkstra.h"
#include "mylabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 部件
    myLabel* picBox;
    QLabel* title, *sel_title_1, *sel_title_2, *sel_title_3, *sel_title_4;
    QLabel* distanceBox, *pathBox;
    QComboBox* comboBox_1, *comboBox_2;
    QStringList locateList = {"南区宿舍", "图书馆", "信南", "信北", "行远楼",
                  "五子顶", "二五广场", "北操", "体育馆", "北区宿舍",
                  "东操", "东区宿舍"};
    vector<vector<int>> locatePosition;
    QPushButton* calcBtn;

    void mouseMoveEvent(QMouseEvent *event) override{
        qDebug() << event->pos();
    }

//    bool eventFilter(QObject *watched, QEvent *event) override;  //事件滤波器
//    void paintEvent(QPaintEvent *event) override;
    void Painter();     //画图



private:
    Ui::MainWindow *ui;
    stack<int> pathStk;

private slots:
    void calcBtnClicked();

};
#endif // MAINWINDOW_H
