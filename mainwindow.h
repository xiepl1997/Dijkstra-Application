#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "mapform.h"
#include "city.h"
#include "road.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void dijkstra(int u, int v);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    MapForm *mapform;
    City citys[14]={
        City(1,points[0]),
        City(2,points[1]),
        City(3,points[2]),
        City(4,points[3]),
        City(5,points[4]),
        City(6,points[5]),
        City(7,points[6]),
        City(8,points[7]),
        City(9,points[8]),
        City(10,points[9]),
        City(11,points[10]),
        City(12,points[11]),
        City(13,points[12]),
        City(14,points[13])
    };
    Road roads[18]={
        Road(citys[0],citys[2]),
        Road(citys[0],citys[4]),
        Road(citys[1],citys[2]),
        Road(citys[2],citys[3]),
        Road(citys[2],citys[7]),
        Road(citys[4],citys[7]),
        Road(citys[1],citys[3]),
        Road(citys[3],citys[5]),
        Road(citys[3],citys[6]),
        Road(citys[5],citys[7]),
        Road(citys[6],citys[9]),
        Road(citys[5],citys[9]),
        Road(citys[7],citys[8]),
        Road(citys[7],citys[11]),
        Road(citys[7],citys[10]),
        Road(citys[8],citys[11]),
        Road(citys[6],citys[12]),
        Road(citys[10],citys[13])
    };
    int start1 = -1;//乘车人起点
    int end1 = -1;//乘车人终点
    int start2 = -1;//拼车人起点
    int end2 = -1;//拼车人终点
    int path[14][14]; //path[i][j]记录i到j路径上，顶点j的前驱。

};

#endif // MAINWINDOW_H
