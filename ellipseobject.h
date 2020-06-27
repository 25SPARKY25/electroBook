#ifndef ELLIPSEOBJECT_H
#define ELLIPSEOBJECT_H
#pragma once

class ellipseObject:public QGraphicsObject
{
    Q_OBJECT
public:
    ellipseObject();
    ellipseObject(qreal x, qreal y, qreal width, qreal height, QColor color);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    QRectF boundingRect() const override;

    qreal getX() const;
    qreal getY() const;
    qreal getWidth() const;
    qreal getHeight() const;


private:
    qreal m_x, m_y, m_width, m_height;
    QColor m_color;
};

#endif // ELLIPSEOBJECT_H
