#include "view.h"

View::View(int width, int height)
{
    scaled(width, height);
    fill(QColor("red"));
}

void View::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->begin(this);
    painter->drawLine(0,0,100,100);
}
