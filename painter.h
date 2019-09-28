#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

class Painter: public QObject
{
    Q_OBJECT
public:
    Painter(QWidget *parent);

public slots:
    void draw();
};

#endif // PAINTER_H
