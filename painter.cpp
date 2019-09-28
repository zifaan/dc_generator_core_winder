#include "painter.h"

Painter::Painter(QWidget *parent)
{

}

void Painter::draw()
{
    qDebug() << "its working";
    QPainter *painter = new QPainter(QWidget);
    painter->drawLine(0,0,100,100);
}
