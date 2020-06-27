#ifndef PAINTSCENE_H
#define PAINTSCENE_H

class paintscene: public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintscene(QObject *parent = 0);
    ~paintscene();

public slots:
    void setPenRadius(int r);

private:
    QPointF     previousPoint;      // Координаты предыдущей точки
    int radius=50; //радиус ручки

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PAINTSCENE_H
