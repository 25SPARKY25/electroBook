#ifndef ANIMATEDPERCEPTRONE_H
#define ANIMATEDPERCEPTRONE_H
#pragma once
#include <QObject>
#include "ellipseobject.h"
#include "lineobject.h"
#include "triangleobject.h"

class animatedPerceptrone:public QObject
{
    Q_OBJECT
public:
    animatedPerceptrone(QGraphicsScene &scene, QTextBrowser &textEdit);
    //публичные методы анимации

    //сенсоры

    void animateSensors();

    //слои
    void animateInpuLayer();
    void animateHidenLayer();
    void animateOutputLayer();

    //коннекты
    void animateSensorConnections();
    void animateHidenConnections();
    void animateOutputConnections();

    //надписи
    void animateLabels();
    void animateSensorLabels();
    void animateFirstNeuronLabels();
    void animateSecondNeuronLabels();
    void animateOutputNeuronLabels();
    void animateLayerLable();

    void changeFirstNeuronLabels();
    void changeSecondNeuronLabels();
    void changeOutputNeuronLabels();


    //проход сигналов
    //вперёд
    void animateSensSignals();
    void animateInpSignals();
    void animateHidSignals();
    //назад
    void animateBackHidSignals();
    void animateBackInpSignals();
    void animateBackSensSignals();



    void blinkSensConnection();
    void blinkFirstConnection();
    void blinkSecondConnection();

    //установка напрвления анимации
    void setAnimateFlag(bool flag);


    void animateAllComponents();    //анимация всех составляющих комонентов

signals:
    void animationFinished();

private:
    qreal w, h;
    bool animateFlag;
    QGraphicsScene &m_ref_scene;
    QTextBrowser &m_ref_textEdit;

    //контейнеры

    //сенсоры
    QVector<triangleobject*> m_sensors;

    //слои
    QVector<ellipseObject*> m_inputLayer;
    QVector<ellipseObject*> m_hidenLayer;
    QVector<ellipseObject*> m_outputLayer;
    //блинки
    QVector<ellipseObject*> m_blinkInputLayer;
    QVector<ellipseObject*> m_blinkHidenLayer;
    QVector<ellipseObject*> m_blinkOutputLayer;

    //сигналы
    QVector<ellipseObject*> m_sensorSignals;
    QVector<ellipseObject*> m_hidenSignals;
    QVector<ellipseObject*> m_outputSignals;

    QVector<ellipseObject*> m_backSensorSignals;
    QVector<ellipseObject*> m_backBlinkHidSignals;
    QVector<ellipseObject*> m_backBlinkOutSignals;
    //соединения
    QVector<lineObject*> m_sensorconnections;
    QVector<lineObject*> m_hidenconnections;
    QVector<lineObject*> m_outputconnections;

    QVector<lineObject*> m_blinkSensorConnections;
    QVector<lineObject*> m_blinkhidenconnections;
    QVector<lineObject*> m_blinkoutputconnections;

    //надписи
    QVector<QGraphicsTextItem*> m_sensorsLabel;
    QVector<QGraphicsTextItem*> m_firstNeuronLabel;
    QVector<QGraphicsTextItem*> m_secondNeuronLabel;
    QVector<QGraphicsTextItem*> m_outputNeuronLabel;
    QVector<QGraphicsTextItem*> m_weightsLabel;
    QVector<QGraphicsTextItem*> m_layerLabel;
//    QVector<QGraphicsTextItem*> m_sensorWeightLabel;
//    QVector<QGraphicsTextItem*> m_hidenWeightLabel;
//    QVector<QGraphicsTextItem*> m_outputWeightLabel;
    QVector<QGraphicsTextItem*> m_outputActivationLabel;
    QVector<QGraphicsTextItem*> m_hidenActivationLabel;
                    //контейнеры//


    //анимации

    //слои
//    QParallelAnimationGroup m_parInpAn;
//    QParallelAnimationGroup m_parHidenAn;
//    QParallelAnimationGroup m_parOutAn;
    //коннекты
//    QParallelAnimationGroup m_parHidenConnAn;
//    QParallelAnimationGroup m_parOutputConnAn;
    //надписи
//    QParallelAnimationGroup m_parLabels;
    //сигналы
    QParallelAnimationGroup m_parSensSig;
    QParallelAnimationGroup m_parHidSig;
    QParallelAnimationGroup m_parOutSig;
    QParallelAnimationGroup m_parBackOutSig;
    QParallelAnimationGroup m_parBackHidSig;
    QParallelAnimationGroup m_parBackInpSig;
    //блинки
    QParallelAnimationGroup m_parHideBlink;
    QParallelAnimationGroup m_parOutBlink;
    QParallelAnimationGroup m_parBackBlinkOutSig;
    QParallelAnimationGroup m_parBackBlinkHidSig;
    QParallelAnimationGroup m_parBackBlinkInpSig;

    QParallelAnimationGroup m_parBackBlinkSensCon;
    QParallelAnimationGroup m_parBackBlinkFirstCon;
    QParallelAnimationGroup m_parBackBlinkSecondCon;



    QParallelAnimationGroup m_par;//для уменьшения количества перменных с типом анимация
                //анимации//

    void createSensors();
    void createInputLayer();
    void createHidenLayer();
    void createOutputLayer();   
    ///создаёт соединения, подписи и сигналы для нейронов
    void createConnections(QVector<ellipseObject*> &targetEll, QVector<ellipseObject*> &sourceEll, QVector<lineObject*> &connections, QVector<ellipseObject*> &Signals, QString num, QVector<lineObject*> &blinkconnections);
    ///

    void createSensorConnections();

    void animateConnections(QVector<lineObject*> &connections, QParallelAnimationGroup &par);
    void blink(QVector<ellipseObject*> &layer, QParallelAnimationGroup &par);
    void animateLayer(QVector<ellipseObject*> &layer, QParallelAnimationGroup &par);
    void animateSignals(QVector<ellipseObject*> &Signals, QVector<lineObject*> &connections, QVector<ellipseObject*> &layer, QParallelAnimationGroup &blinkan, QParallelAnimationGroup &par, bool forward=true);
    void animateSensorSignals(bool forward=true);
    void animateBlinkConnection(QVector<lineObject*> &blinkconnections, QParallelAnimationGroup &par);
    void createBackBlinkSignal(QVector<lineObject*> &connections, QVector<ellipseObject*> &Signals);
    void createLayerLabel();

    void chandeWeightsLabels(int startIndex, int finishIndex, int num);

    template<typename T>
    void animateObject(QVector<T*> obj);

};

#endif // ANIMATEDPERCEPTRONE_H
