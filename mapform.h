#ifndef MAPFORM_H
#define MAPFORM_H

#include <QWidget>
#include<QPointF>
#include<QColor>
#include<road.h>
#include<city.h>

//12个地点的坐标
const QPointF points[14]={
    QPointF(50,70),
    QPointF(300,40),
    QPointF(100,120),
    QPointF(200,140),
    QPointF(10,220),
    QPointF(180,190),
    QPointF(350,170),
    QPointF(130,250),
    QPointF(10,330),
    QPointF(300,340),
    QPointF(150,360),
    QPointF(40,380),
    QPointF(250,250),
    QPointF(200,345)
};

//邻接矩阵
//double matrix[12][12];

namespace Ui {
class MapForm;
}

class MapForm : public QWidget
{
    Q_OBJECT

public:
    explicit MapForm(QWidget *parent = 0);
    ~MapForm();
    void paintEvent(QPaintEvent *);

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
    double matrix[14][14];

private:
    Ui::MapForm *ui;
};

#endif // MAPFORM_H
