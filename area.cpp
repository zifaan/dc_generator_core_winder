#include "area.h"

Area::Area()
{

}

void Area::draw()
{
    QPainter *painter = new QPainter();
    painter->drawLine(10,10,200,200);
}
