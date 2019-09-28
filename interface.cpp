#include "interface.h"

Interface::Interface()
{
    setFixedSize(awidth, aheight);

    //draw the buttons
    QPushButton *btn = new QPushButton("Draw", this);
    lap = new QRadioButton("Lap", this);
    wave = new QRadioButton("Wave", this);
    z_line = new QLineEdit(this);
    p_line = new QLineEdit(this);
    //yb_line = new QLineEdit(this);
    //yf_line = new QLineEdit(this);
    QLabel *z_label = new QLabel("Conductors(Z)",this);
    QLabel *p_label = new QLabel("Poles(P)",this);
    //QLabel *yb_label = new QLabel("Back Pitch(Yb)",this);
    //QLabel *yf_label = new QLabel("Front Pitch(Yf)",this);
    z_label->setGeometry(10,10,70,30);
    z_line->setGeometry(90,10,50,30);
    p_label->setGeometry(150,10,50,30);
    p_line->setGeometry(210,10,50,30);
    //yb_label->setGeometry(270,10,70,30);
    //yb_line->setGeometry(350,10,50,30);
    //yf_label->setGeometry(410,10,50,30);
    //yf_line->setGeometry(470,10,50,30);
    lap->setGeometry(270,10,50,30);
    wave->setGeometry(330,10,50,30);
    btn->setGeometry(390,10,50,30);

    //draw area
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,awidth,aheight);
    view = new QGraphicsView(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setGeometry(0,50,awidth,aheight-50);
    view->setScene(scene);
    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(draw()));
}

void Interface::lapWind(QPainter *painter)
{
    int z = z_line->text().toInt();
    int p = p_line->text().toInt();
    int yb = (((z/p)*2) + 2)/2;
    int yf = yb-2;
    //draw conductors
    int spacing = 20;
    int xstart = (width()/2)-(((z*spacing)-10)/2);
    int ystart = (height()/2)-50 ;
    int yend = (height()/2)+50 ;
    for (int i = 0; i < z; i++)
    {
        if((i%2) == 0)
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+(i*spacing),ystart,xstart+(i*spacing),yend);
            painter->setPen(Qt::blue);
            painter->drawText(xstart+(i*spacing), yend, QString::number(i+1));
        }
        else
        {
            painter->setPen(Qt::PenStyle(Qt::DashLine));
            painter->drawLine(xstart+(i*spacing),ystart,xstart+(i*spacing),yend);
            painter->setPen(Qt::blue);
            painter->drawText(xstart+(i*spacing), yend-20, QString::number(i+1));
        }
    }

    //do calculations
    QVector<int> s, m, e;
    s.append(1);
    for (int k = 0; k > -1; k++)
    {
        m.append(s[k]+yb);
        if(((s[k]+yb)-z)==1)
        {
            break;
        }
        e.append(m[k]-yf);
        if(((m[k]-yf)-z)==1)
        {
            break;
        }
        s.append(e[k]);
    }
    //draw winding design
    int top = ((m[0]-s[0])*spacing)/2;
    int bot = ((m[0]-e[0])*spacing)/2;
    for (int np=0;np < s.size();np++)
    {
        //qDebug() << s[np] << "+" << yb << "="<< m[np] << "\t" << m[np] << "+" << yf << "=" << e[np];
        if ((m[np]-z) > 0)
        {
            painter->setPen(Qt::PenStyle(Qt::DashLine));
            painter->drawLine(xstart+((m[np]-z)*spacing)-spacing, ystart, xstart+((m[np]-z)*spacing)-top-spacing, ystart-30);
            painter->drawLine(xstart+((m[np]-z)*spacing)-spacing, yend, xstart+((m[np]-z)*spacing)-bot-spacing, yend+30);
        }
        else
        {
            painter->setPen(Qt::PenStyle(Qt::DashLine));
            painter->drawLine(xstart+(m[np]*spacing)-spacing, ystart, xstart+(m[np]*spacing)-top-spacing, ystart-30);
            painter->drawLine(xstart+(m[np]*spacing)-spacing, yend, xstart+(m[np]*spacing)-bot-spacing, yend+30);
        }
        if ((e[np]-z) > 0)
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+((e[np]-z)*spacing)-spacing, yend, xstart+((e[np]-z)*spacing)+bot-spacing, yend+30);
        }
        else
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+(e[np]*spacing)-spacing, yend, xstart+(e[np]*spacing)+bot-spacing, yend+30);
        }
        if ((s[np]-z) > 0)
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+((s[np]-z)*spacing)-spacing, ystart, xstart+((s[np]-z)*spacing)+top-spacing, ystart-30);
        }
        else
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+(s[np]*spacing)-spacing, ystart, xstart+(s[np]*spacing)+top-spacing, ystart-30);
        }
    }
    Table *win = new Table(s, m, e, 1, yb, yf);
    win->show();
}

void Interface::waveWind(QPainter *painter)
{
    int z = z_line->text().toInt();
    int p = p_line->text().toInt();
    //int yb = yb_line->text().toInt();
    //int yf = yf_line->text().toInt();
    int yb = 0;
    int yf = 0;
    if (((z+2)/p) % 2 == 1)
    {
        yb = (z+2)/p;
        yf = yb;
    }
    else
    {
        yb = (z-2)/p;
        yf = yb;
    }
    //draw conductors
    int spacing = 20;
    int xstart = (width()/2)-(((z*spacing)-10)/2);
    int ystart = (height()/2)-50 ;
    int yend = (height()/2)+50 ;
    for (int i = 0; i < z; i++)
    {
        if((i%2) == 0)
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+(i*spacing),ystart,xstart+(i*spacing),yend);
            painter->setPen(Qt::blue);
            painter->drawText(xstart+(i*spacing), yend, QString::number(i+1));
        }
        else
        {
            painter->setPen(Qt::PenStyle(Qt::DashLine));
            painter->drawLine(xstart+(i*spacing),ystart,xstart+(i*spacing),yend);
            painter->setPen(Qt::blue);
            painter->drawText(xstart+(i*spacing), yend-20, QString::number(i+1));
        }
    }
    //do calculations
    QVector<int> s, m, e;
    s.append(1);
    for (int k = 0; k > -1; k++)
    {
        if(((s[k]+yb)-z) > 0)
        {
            m.append((s[k]+yb)-z);
            if(((s[k]+yb)-z) == 1)
            {
                break;
            }
        }
        else
        {
            m.append(s[k]+yb);
        }

        if(((m[k]+yb)-z) > 0)
        {
            e.append((m[k]+yb)-z);
            if(((m[k]+yb)-z) == 1)
            {
                break;
            }
        }
        else
        {
            e.append(m[k]+yb);
        }
        s.append(e[k]);
    }
    //draw winding design
    int top = ((m[0]-s[0])*spacing)/2;
    int bot = ((m[0]-e[0])*spacing)/2;
    for (int np=0;np < s.size();np++)
    {
        //qDebug() << s[np] << "+" << yb << "="<< m[np] << "\t" << m[np] << "+" << yf << "=" << e[np];
        if ((m[np]-z) > 0)
        {
            painter->setPen(Qt::PenStyle(Qt::DashLine));
            painter->drawLine(xstart+((m[np]-z)*spacing)-spacing, ystart, xstart+((m[np]-z)*spacing)-top-spacing, ystart-30);
            painter->drawLine(xstart+((m[np]-z)*spacing)-spacing, yend, xstart+((m[np]-z)*spacing)-bot-spacing, yend+30);
        }
        else
        {
            painter->setPen(Qt::PenStyle(Qt::DashLine));
            painter->drawLine(xstart+(m[np]*spacing)-spacing, ystart, xstart+(m[np]*spacing)-top-spacing, ystart-30);
            painter->drawLine(xstart+(m[np]*spacing)-spacing, yend, xstart+(m[np]*spacing)-bot-spacing, yend+30);
        }
        if ((e[np]-z) > 0)
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+((e[np]-z)*spacing)-spacing, yend, xstart+((e[np]-z)*spacing)+bot-spacing, yend+30);
        }
        else
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+(e[np]*spacing)-spacing, yend, xstart+(e[np]*spacing)+bot-spacing, yend+30);
        }
        if ((s[np]-z) > 0)
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+((s[np]-z)*spacing)-spacing, ystart, xstart+((s[np]-z)*spacing)+top-spacing, ystart-30);
        }
        else
        {
            painter->setPen(Qt::PenStyle(Qt::SolidLine));
            painter->drawLine(xstart+(s[np]*spacing)-spacing, ystart, xstart+(s[np]*spacing)+top-spacing, ystart-30);
        }
    }
    Table *win = new Table(s, m, e, 2, yb, yf);
    win->show();
}

void Interface::draw()
{
    QPixmap *map = new QPixmap(awidth,aheight-50);
    map->fill(QColor("white"));
    QPainter *painter = new QPainter(map);
    painter->begin(map);
    if (lap->isChecked() == true)
    {
        lapWind(painter);
    }
    else if (wave->isChecked() == true)
    {
        waveWind(painter);
    }
    painter->end();
    delete painter;
    scene->addPixmap(*map);
}
