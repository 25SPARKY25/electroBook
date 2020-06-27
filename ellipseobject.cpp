#include "recognize_digit_cpp/stdafx.h"
#include "ellipseobject.h"

ellipseObject::ellipseObject()
{

}

ellipseObject::ellipseObject(qreal x, qreal y, qreal width, qreal height, QColor color)
{
    this->m_x = x;
    this->m_y = y;
    this->m_width = width;
    this->m_height = height;
    this->m_color = color;
    this->setTransformOriginPoint(x, y);
    this->setVisible(false);
}

void ellipseObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
        Q_UNUSED(widget)
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(m_color);
        painter->setBrush(QBrush(m_color, Qt::SolidPattern));
        QRectF rect = boundingRect();
        painter->drawEllipse(rect);
}

QRectF ellipseObject::boundingRect() const
{
    return QRectF(this->m_x, this->m_y, this->m_width, this->m_height);
}

qreal ellipseObject::getX() const
{
    return this->m_x;
}

qreal ellipseObject::getY() const
{
    return this->m_y;
}

qreal ellipseObject::getWidth() const
{
    return this->m_width;
}

qreal ellipseObject::getHeight() const
{
    return this->m_height;
}
