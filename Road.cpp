#include "road.h"
#include "qmath.h"
#include "QLineF"
#include "city.h"

Road::Road(City c1, City c2)
{
    city1 = c1;
    city2 = c2;
    line = QLineF(c1.addr, c2.addr);
    length = line.length();
    //color = QColor(0,0x00,0);
    color = "black";
}
Road::Road()
{

}
