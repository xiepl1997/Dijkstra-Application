#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "city.h"
#include "mapform.h"
#include "QMessageBox"
#include "math.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mapform = new MapForm(this);
    mapform->show();
    ui->scrollArea->setWidget(mapform);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int result_path[14]; //result_path用于存储起点到终点最短路径所经过的点

//触发路线规划
void MainWindow::on_pushButton_clicked()
{
    int f1 = 0;//标记乘车人是否添加偏好，0未添加，1添加
    int f2 = 0;//标记拼车人是否被加入，0未加入，1加入
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    QString str3 = ui->comboBox_3->currentText();
    QString str4 = ui->comboBox_4->currentText();
    QString str5 = ui->comboBox_5->currentText();
    if(str1 == str2)
    {
        QMessageBox::about(NULL, "提示", "乘车人存在起点和终点一致的情况，请重新选择!");
        return;
    }
    if(str5 != "None")
    {
        f1 = 1;
    }
    if((str3 == "-"&&str4 != "-") ||(str3 != "-" && str4 == "-"))
    {
        QMessageBox::about(NULL, "提示", "拼车人起点终点未输入完全!");
        return;
    }
    if(str3 == str4 && str3 != "-" && str4 != "-")
    {
        QMessageBox::about(NULL, "提示", "拼车人存在起点和终点一致的情况，请重新选择!");
        return;
    }
    if(str3 != "-" && str4 != "-")
    {
        f2 = 1; //有拼车人
        start2 = str3.toInt();
        end2 = str4.toInt();
    }


    start1 = str1.toInt(); // 乘车人起点
    end1 = str2.toInt(); //乘车人终点

    if(f1 == 0 && f2 == 0) //无偏好、无拼车人
    {
        dijkstra(start1-1, end1-1);

        memset(result_path, 0, sizeof(result_path));
        result_path[0] = end1;

        int m = start1 - 1;
        int n = end1 - 1;
        //获取路径
        for(int i = 1; i < 14; i++)
        {
            if(m == n)
            {
                //result_path[i] = start1 + 1;
                break;
            }
            result_path[i] = path[m][n] + 1;
            n = path[m][n];
        }
    }

    //重绘图示，将该路径在图示中标红
    //先将颜色设为黑色
    for(int i = 0; i < 14; i++)
    {
        mapform->citys[i].color = "black";
    }
    for(int i = 0; i < 18; i++)
    {
        mapform->roads[i].color = "black";
    }
    //m = start1 - 1;
    for(int i = 0; ; i++)
    {
        if(result_path[i] == 0)
            break;
        //该路径中的地点标红
        mapform->citys[result_path[i]-1].color = "red";
        //该路径中的道路标红
        if(result_path[i+1] != 0)
        {
            for(int j = 0; j < 18; j++){
                int c1 = mapform->roads[j].city1.name;
                int c2 = mapform->roads[j].city2.name;
                if((c1 == result_path[i] && c2 == result_path[i+1]) || (c1 == result_path[i+1] && c2 == result_path[i]))
                {
                    mapform->roads[j].color = Qt::red;
                    break;
                }
            }
        }
    }
    //刷新图示
    mapform->update();

}

double dis[14]; //存储估计值
int flag[14]; //flag[i]代表i这个点有没有被当做源点去搜索过，1为有，0为没有
//最短路径算法，用path[][]记录最短路线前驱
void MainWindow::dijkstra(int u, int v)
{
    QString str = "";
    for(int i = 0; i < 14; i++)
    {
        dis[i] = 0x3f3f3f3f;
    }
    for(int i = 0; i < 14; i++)
    {
        for(int j = 0; j < 14; j++)
        {
            path[i][j] = 0;
        }
    }
    memset(flag, 0, sizeof(flag));
    int start = u; //从源点搜索
    flag[start] = 1;
    dis[start] = 0;

    for(int i = 0; i < 14; i++)
    {
        if(i != start)
        {
            if(dis[i] > mapform->matrix[u][i]) //记录前驱
            {
                path[u][i] = u;
            }
            dis[i] = qMin(dis[i], mapform->matrix[u][i]);
        }
    }

    for(int i = 0; i < 14-1; i++)
    {
        int minn = 0x3f3f3f3f;
        //int temp = start;
        for(int j = 0; j < 14; j++)
        {
            if(flag[j] == 0 && minn > dis[j])
            {
                minn = dis[j];
                start = j;
            }
            if(i == 0)
            {
                path[u][start] = u;
            }
        }
        flag[start] = 1;
        //path[u][start] = temp;
        for(int j = 0; j < 14; j++)
        {
            if(flag[j] == 0)
            {
                if(dis[j] > dis[start] + mapform->matrix[start][j]) //记录前驱
                {
                    path[u][j] = start;
                }
                dis[j] = qMin(dis[j], dis[start] + mapform->matrix[start][j]);
            }
        }
    }
}






















