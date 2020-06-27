#include "line.h"

line::line()
{
    m_line = new QGraphicsLineItem;
}

QPointF line::endPoint() const
{
    QLineF l = this->m_line->line();
    return l.p2();
}

QPointF line::setEndPoint(const QPointF &pt)
{
    QLineF l = this->m_line->line();
        l.setP2(pt);
        this->m_line->setLine(l);
}
