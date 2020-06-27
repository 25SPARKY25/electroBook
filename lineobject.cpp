#include "recognize_digit_cpp/stdafx.h"
#include "lineobject.h"

lineObject::lineObject()
{

}

lineObject::lineObject(qreal x1, qreal y1, qreal x2, qreal y2, QColor color)
{
    this->m_x1 = x1;
    this->m_y1 = y1;
    this->m_x2 = x2;
    this->m_y2 = y2;
    this->m_color = color;
    this->setTransformOriginPoint(x1, y1);
    this->setVisible(false);
}

void lineObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
        Q_UNUSED(widget)
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(m_color);
        painter->setBrush(QBrush(m_color, Qt::SolidPattern));
        m_line = line();
        painter->drawLine(m_line);
}

QLineF lineObject::line() const
{
    return QLineF(this->m_x1, this->m_y1, this->m_x2, this->m_y2);
}

QRectF lineObject::boundingRect() const
{
    return QRectF(this->m_x1, this->m_y1, this->m_x2 - this->m_x1, this->m_y2 - this->m_y1);
}

QPointF lineObject::getMiddlePoint()
{
    qreal x, y;
    x = (this->m_x1+this->m_x2)/2;
    y = (this->m_y1+this->m_y2)/2;
    return QPointF((this->m_x1+x)/2-20,(this->m_y1+y)/2); //получаем координату 1/4 линии
}

qreal lineObject::getX1()
{
    return this->m_x1;
}

qreal lineObject::getY1()
{
    return this->m_y1;
}

qreal lineObject::getX2()
{
    return this->m_x2;
}

qreal lineObject::getY2()
{
    return this->m_y2;
}
