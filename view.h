#ifndef VIEW_H
#define VIEW_H

#include <QPixmap>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>

class View: public QObject, public QPixmap
{
    Q_OBJECT
public:
    View(int width, int height);
    void paintEvent(QPaintEvent *event);
};

#endif // VIEW_H
