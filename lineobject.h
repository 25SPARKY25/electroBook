#ifndef LINEOBJECT_H
#define LINEOBJECT_H
#pragma once


class lineObject:public QGraphicsObject
{
    Q_OBJECT

public:
    lineObject();
    lineObject(qreal x1, qreal y1, qreal x2, qreal y2, QColor color);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    QLineF line() const;
    QRectF boundingRect() const override;
    QPointF getMiddlePoint();
    qreal getX1();
    qreal getY1();
    qreal getX2();
    qreal getY2();



private:
    qreal m_x1, m_y1, m_x2, m_y2;
    QColor m_color;
    QLineF m_line;


};

#endif // LINEOBJECT_H
