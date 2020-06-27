#ifndef TRIANGLEOBJECT_H
#define TRIANGLEOBJECT_H

class triangleobject:public QGraphicsObject
{
    Q_OBJECT
public:
    triangleobject();
    triangleobject(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, QColor color);

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    QRectF boundingRect() const override;

    qreal getX1() const;
    qreal getY1() const;
    qreal getX2() const;
    qreal getY2() const;

private:
    qreal m_x1, m_y1, m_x2, m_y2, m_x3, m_y3, m_width, m_height;
    QColor m_color;
    QVector<QPointF> points;
};

#endif // TRIANGLEOBJECT_H
