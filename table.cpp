#include "table.h"

Table::Table(QVector<int> s, QVector<int> m, QVector<int> e, int in, int yb, int yf)
{
    setGeometry(0,0,250,500);
    QTableWidget *tabloid = new QTableWidget(s.size(),2, this);
    tabloid->setGeometry(0,0,250,500);
    QStringList list = {QString("Yb"+QString::number(yb)), QString("Yf="+QString::number(yf))};
    tabloid->setHorizontalHeaderLabels(list);
    if (in == 1)
    {
        for (int p=0; p < s.size(); p++)
        {
            QString str1 = QString::number(s[p]) + "+" + QString::number(yb) + "=" + QString::number(m[p]);
            QString str2 = QString::number(m[p]) + "-" + QString::number(yf) + "=" + QString::number(e[p]);
            tabloid->setItem(p,0,new QTableWidgetItem(str1));
            tabloid->setItem(p,1,new QTableWidgetItem(str2));
        }
    }

    if (in == 2)
    {
        for (int p=0; p < s.size(); p++)
        {
            QString str1 = QString::number(s[p]) + "+" + QString::number(yb) + "=" + QString::number(m[p]);
            QString str2 = QString::number(m[p]) + "+" + QString::number(yf) + "=" + QString::number(e[p]);
            tabloid->setItem(p,0,new QTableWidgetItem(str1));
            tabloid->setItem(p,1,new QTableWidgetItem(str2));
        }
    }
}
