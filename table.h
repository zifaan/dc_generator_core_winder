#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QVector>
#include <QStringList>
class Table: public QWidget
{
public:
    Table(QVector<int> s, QVector<int> m, QVector<int> e, int in, int yb, int yf);
};

#endif // TABLE_H
