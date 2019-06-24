#include "mapform.h"
#include "ui_mapform.h"
#include<QPainter>
#include<QFont>

MapForm::MapForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    //初始化matrix
    for(int i = 0; i < 14; i++)
    {
        for(int j = 0; j < 14; j++)
        {
            if(i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = 0x3f3f3f3f;
        }
    }

    //填充matrix
    for(int i = 0; i < 18; i++)
    {
        matrix[roads[i].city1.name-1][roads[i].city2.name-1] = roads[i].length;
        matrix[roads[i].city2.name-1][roads[i].city1.name-1] = roads[i].length;
    }

}

MapForm::~MapForm()
{
    delete ui;
}

void MapForm::paintEvent(QPaintEvent *)
{
    //绘制地点
    QPainter painter(this);
    for(int i = 0; i < 14; i++)
    {
        QPen pen;
        if(citys[i].color == "black")
            pen.setColor(Qt::black);
        else
            pen.setColor(Qt::black);
        pen.setWidth(8);
        painter.setPen(pen);
        painter.drawPoint(citys[i].addr);
        //painter.drawText(citys[i].addr.x()-2,citys[i].addr.y()-10,QString::number(i+1));
    }

    //绘制地名
    QPainter painter2(this);
    QFont font;
    font.setPointSize(10);
    font.setFamily("Microsoft YaHei");
    font.setLetterSpacing(QFont::AbsoluteSpacing,0);
    painter2.setFont(font);
    for(int i = 0; i < 14; i++)
    {
        painter2.drawText(citys[i].addr.x()-2,citys[i].addr.y()-10,QString::number(i+1));
    }

    //绘制路线
    QPainter painter1(this);
    for(int i = 0; i < 18; i++)
    {
        QPen pen1;
        if(roads[i].color == "black")
        {
            pen1.setColor(Qt::black);
            pen1.setWidth(2);
        }
        else
        {
            pen1.setColor(Qt::red);
            pen1.setWidth(5);
        }
        painter1.setPen(pen1);
        painter1.drawLine(roads[i].city1.addr, roads[i].city2.addr);
    }
}

