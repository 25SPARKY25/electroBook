#include "paintscene.h"

paintscene::paintscene(QObject *parent) : QGraphicsScene(parent)
{

}

paintscene::~paintscene()
{

}

void paintscene::setPenRadius(int r)
{
   this->radius = r;
}

void paintscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // При нажатии кнопки мыши отрисовываем эллипс
    addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               radius,
               radius,
               QPen(Qt::NoPen),
               QBrush(Qt::white, Qt::SolidPattern));
    // Сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
}

void paintscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Отрисовываем линии с использованием предыдущей координаты
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(Qt::white,radius,Qt::DashDotDotLine,Qt::RoundCap));
    // Обновляем данные о предыдущей координате
    previousPoint = event->scenePos();
}
