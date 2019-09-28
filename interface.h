#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGraphicsView>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
//#include <QDebug>
#include <QVector>
#include <QRadioButton>

#include <table.h>

class Interface: public QWidget
{
    Q_OBJECT
public:
    Interface();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QLineEdit *z_line;
    QLineEdit *p_line;
    QLineEdit *yb_line;
    QLineEdit *yf_line;
    QRadioButton *lap;
    QRadioButton *wave;
    int awidth = 1280;
    int aheight = 960;

    void lapWind(QPainter *painter);
    void waveWind(QPainter *painter);

public slots:
    void draw();
};

#endif // INTERFACE_H
