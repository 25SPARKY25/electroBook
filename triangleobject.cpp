#include "recognize_digit_cpp/stdafx.h"
#include "triangleobject.h"

triangleobject::triangleobject()
{

}

triangleobject::triangleobject(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, QColor color)
{
    this->m_x1 = x1;
    this->m_y1 = y1;
    this->m_x2 = x2;
    this->m_y2 = y2;
    this->m_x3 = x3;
    this->m_y3 = y3;
    this->m_color = color;
    this->setTransformOriginPoint(x1, y1);
    this->setVisible(false);
    points<<QPointF(x1, y1)<<QPointF(x2, y2)<<QPointF(x3, y3);
}

void triangleobject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
        Q_UNUSED(widget)
    QPolygonF triangle(points);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(m_color);
        painter->setBrush(QBrush(m_color, Qt::SolidPattern));
        QRectF rect = boundingRect();
        painter->drawPolygon(triangle);
}

QRectF triangleobject::boundingRect() const
{
    return QRectF(this->m_x1, this->m_y1, this->m_x2-this->m_x3, this->m_y3-this->m_y1);
}

qreal triangleobject::getX1() const
{
    return this->m_x1;
}

qreal triangleobject::getY1() const
{
    return this->m_y1;
}

qreal triangleobject::getX2() const
{
    return this->m_x2;
}

qreal triangleobject::getY2() const
{
    return this->m_y2;
}
