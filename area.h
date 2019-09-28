#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QPainter>

class Area: public QObject
{
    Q_OBJECT
public:
    Area();

public slots:
    void draw();
};

#endif // AREA_H
