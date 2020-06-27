#ifndef LINE_H
#define LINE_H

#include <QObject>

class line:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF endPoint READ endPoint WRITE setEndPoint)
public:
    line();
    QPointF endPoint() const;

private:
    QGraphicsLineItem *m_line;

private slots:
    QPointF setEndPoint(const QPointF &pt);
};

#endif // LINE_H
