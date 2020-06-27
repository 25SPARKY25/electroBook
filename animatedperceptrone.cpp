#include "animatedperceptrone.h"

animatedPerceptrone::animatedPerceptrone(QGraphicsScene &scene, QTextBrowser &textEdit):m_ref_scene(scene), m_ref_textEdit(textEdit)
{

}

void animatedPerceptrone::animateSensors()
{

    h = m_ref_scene.sceneRect().height();
    w = m_ref_scene.sceneRect().width();
    createSensors();
    createInputLayer();
    createHidenLayer();
    createOutputLayer();
    //создаём для прохода вперёд
    createSensorConnections();
    createConnections(m_hidenLayer, m_inputLayer, m_hidenconnections, m_hidenSignals, "2", m_blinkhidenconnections);
    createConnections(m_outputLayer, m_hidenLayer, m_outputconnections, m_outputSignals, "3", m_blinkoutputconnections);
    //создаём для прохода назад
    createBackBlinkSignal(m_hidenconnections, m_backBlinkHidSignals);
    createBackBlinkSignal(m_outputconnections, m_backBlinkOutSignals);


    createLayerLabel();

    animateObject(m_sensors);
}


void animatedPerceptrone::animateLayer(QVector<ellipseObject *> &layer, QParallelAnimationGroup &par)
{
    par.clear();
    QVector<QPropertyAnimation*> inpAnim;
    for(int i = 0; i<layer.size(); i++)
    {
        inpAnim.push_back(new QPropertyAnimation(layer[i], "scale"));
        inpAnim.last()->setDuration(1000);

        if(animateFlag)
        {
            inpAnim.last()->setStartValue(0);
            inpAnim.last()->setEndValue(1);
        }
        else
        {
            inpAnim.last()->setStartValue(1);
            inpAnim.last()->setEndValue(0);
        }
        par.addAnimation(inpAnim.last());
        if(!layer[i]->isActive())
        {m_ref_scene.addItem(layer[i]);}
        connect(&par, &QParallelAnimationGroup::stateChanged, [layer, i](){layer[i]->setVisible(true);});
    }
    par.start();
}

void animatedPerceptrone::animateSignals(QVector<ellipseObject *> &Signals, QVector<lineObject*> &connections, QVector<ellipseObject*> &layer, QParallelAnimationGroup &blinkan, QParallelAnimationGroup &par, bool forward)
{
    par.clear();
    QVector<QPropertyAnimation*> inpAnim;
    for(int i = 0; i<Signals.size(); i++)
    {
        inpAnim.push_back(new QPropertyAnimation(Signals[i], "pos"));
        inpAnim.last()->setDuration(1000);
        if(forward)
        {
            inpAnim.last()->setStartValue(QPointF(0, -Signals[i]->getHeight()/2));
            inpAnim.last()->setEndValue(QPointF(connections[i]->getX2() - Signals[i]->getX(), connections[i]->getY2()-Signals[i]->getY()-Signals[i]->getHeight()/2));
        }
        else
        {
            inpAnim.last()->setStartValue(QPointF(0, -Signals[i]->getHeight()/2));
            inpAnim.last()->setEndValue(QPointF(connections[i]->getX1() - Signals[i]->getX(), connections[i]->getY1()-Signals[i]->getY()-Signals[i]->getHeight()/2));
        }
        par.addAnimation(inpAnim.last());
        if(!Signals[i]->isActive())
        {m_ref_scene.addItem(Signals[i]);}
        connect(&par, &QParallelAnimationGroup::stateChanged, [Signals, i](){Signals[i]->setVisible(true);});
        connect(&par, &QParallelAnimationGroup::finished, [Signals, i](){Signals[i]->setVisible(false);});
    }
    connect(&par, &QParallelAnimationGroup::finished, [this, &layer, &blinkan](){blink(layer, blinkan);});
    par.start();
}

void animatedPerceptrone::animateSensorSignals(bool forward)
{
    m_parSensSig.clear();
    QVector<QPropertyAnimation*> inpAnim;
    for(int i = 0; i<m_sensorSignals.size(); i++)
    {
        inpAnim.push_back(new QPropertyAnimation(m_sensorSignals[i], "pos"));
        inpAnim.last()->setDuration(1000);
        if(forward)
        {
            inpAnim.last()->setStartValue(QPointF(0, -m_sensorSignals[i]->getHeight()/2));
            inpAnim.last()->setEndValue(QPointF(m_sensorconnections[i]->getX2() - m_sensorSignals[i]->getX(), m_sensorconnections[i]->getY2()-m_sensorSignals[i]->getY()-m_sensorSignals[i]->getHeight()/2));
        }
        else
        {
            inpAnim.last()->setStartValue(QPointF(0, -m_sensorSignals[i]->getHeight()/2));
            inpAnim.last()->setEndValue(QPointF(m_sensorconnections[i]->getX1() - m_sensorSignals[i]->getX(), m_sensorconnections[i]->getY1()-m_sensorSignals[i]->getY()-m_sensorSignals[i]->getHeight()/2));
        }
        m_parSensSig.addAnimation(inpAnim.last());
        if(!m_sensorSignals[i]->isActive())
        {m_ref_scene.addItem(m_sensorSignals[i]);}
        connect(&m_parSensSig, &QParallelAnimationGroup::stateChanged, [this, i](){m_sensorSignals[i]->setVisible(true);});
        connect(&m_parSensSig, &QParallelAnimationGroup::finished, [this, i](){m_sensorSignals[i]->setVisible(false);});
    }
    connect(&m_parSensSig, &QParallelAnimationGroup::finished, [this](){blink(m_blinkInputLayer, m_parBackBlinkInpSig);});
    m_parSensSig.start();
}

void animatedPerceptrone::animateBlinkConnection(QVector<lineObject *> &blinkconnections, QParallelAnimationGroup &par)
{
    par.clear();
    QVector<QPropertyAnimation*> blinkAnim;
    for(int i = 0; i<blinkconnections.size(); i++)
    {
        if(!blinkconnections[i]->isActive())
        {m_ref_scene.addItem(blinkconnections[i]);}
        blinkAnim.push_back(new QPropertyAnimation(blinkconnections[i], "opacity"));
        blinkAnim.last()->setDuration(1000);
        blinkAnim.last()->setStartValue(1);
        blinkAnim.last()->setEndValue(0);
        par.addAnimation(blinkAnim.last());

        connect(&par, &QParallelAnimationGroup::stateChanged, [blinkconnections, i](){blinkconnections[i]->setVisible(true);});
    }
    connect(&par, &QParallelAnimationGroup::finished, [this](){emit(animationFinished());});
    par.start();
}

void animatedPerceptrone::createBackBlinkSignal(QVector<lineObject *> &connections, QVector<ellipseObject *> &Signals)
{
    for(int z=0; z<connections.size(); z++)
    {
        ///создайм сигналы
        Signals.push_back(new ellipseObject(connections[z]->getX2(), connections[z]->getY2(), 10, 10 ,Qt::green));
        m_ref_scene.addItem(Signals.last());
    }
}

void animatedPerceptrone::createLayerLabel()
{
    m_layerLabel.push_back(new QGraphicsTextItem("Сенсоры"));
    m_layerLabel.last()->setVisible(false);
    m_layerLabel.last()->setPos(w/12, h/5);
    m_layerLabel.push_back(new QGraphicsTextItem("Входной слой"));
    m_layerLabel.last()->setVisible(false);
    m_layerLabel.last()->setPos(w/12*3, h/5);
    m_layerLabel.push_back(new QGraphicsTextItem("Скрытый слой"));
    m_layerLabel.last()->setVisible(false);
    m_layerLabel.last()->setPos(w/12*6, h/5);
    m_layerLabel.push_back(new QGraphicsTextItem("Внешний слой"));
    m_layerLabel.last()->setVisible(false);
    m_layerLabel.last()->setPos(w/12*9, h/5);
}

void animatedPerceptrone::chandeWeightsLabels(int startIndex, int finishIndex, int num)
{
    int c=0;
    for(int i=startIndex; i<finishIndex; i++)
    {
        m_weightsLabel[i]->setPlainText("W`"+QString::number(num)+", "+QString::number(c+1));
        c++;
    }
}

void animatedPerceptrone::setAnimateFlag(bool flag)
{
    animateFlag = flag;
}

void animatedPerceptrone::animateAllComponents()
{

    animateLayerLable();
    animateLabels();
    animateOutputNeuronLabels();
    animateOutputLayer();

    animateOutputConnections();
    animateSecondNeuronLabels();
    animateHidenLayer();

    animateHidenConnections();
    animateFirstNeuronLabels();
    animateInpuLayer();

    animateSensorConnections();
    animateSensorLabels();
    animateSensors();
}

void animatedPerceptrone::createSensors()
{
    m_sensors.push_back(new triangleobject(w/12, h/3, w/12+50, h/3+25, w/12, h/3+50, Qt::green));
    m_sensors.push_back(new triangleobject(w/12, (h/3)*2, w/12+50, (h/3)*2+25, w/12, (h/3)*2+50, Qt::green));
    ///создаём метки весов
    m_sensorsLabel.push_back(new QGraphicsTextItem("X1"));
    m_sensorsLabel.last()->setVisible(false);
    m_sensorsLabel.last()->setPos( w/12+12, h/3+12);

    m_sensorsLabel.push_back(new QGraphicsTextItem("X2"));
    m_sensorsLabel.last()->setVisible(false);
    m_sensorsLabel.last()->setPos(w/12+12, h/3*2+12);
}

void animatedPerceptrone::animateInpuLayer()
{
    animateObject(m_inputLayer);
}

void animatedPerceptrone::animateHidenLayer()
{
    animateObject(m_hidenLayer);
}

void animatedPerceptrone::animateOutputLayer()
{
    animateObject(m_outputLayer);
}

void animatedPerceptrone::animateSensorConnections()
{
    animateObject(m_sensorconnections);
}

void animatedPerceptrone::animateConnections(QVector<lineObject*> &connections, QParallelAnimationGroup &par)
{
    par.clear();
    QVector<QPropertyAnimation*> inpAnim;
    for(int z=0; z<connections.size(); z++)
    {
        if(!connections[z]->isActive())
        {m_ref_scene.addItem(connections[z]);}
        inpAnim.push_back(new QPropertyAnimation(connections[z], "scale"));
        inpAnim.last()->setDuration(1000);

        if(animateFlag)
        {
            inpAnim.last()->setStartValue(0);
            inpAnim.last()->setEndValue(1);
        }
        else
        {
            inpAnim.last()->setStartValue(1);
            inpAnim.last()->setEndValue(0);
        }
        par.addAnimation(inpAnim.last());
        connect(&par, &QParallelAnimationGroup::stateChanged, [connections, z]()
        {
            connections[z]->setVisible(true);
        });
    }
    par.start();
}

void animatedPerceptrone::blink(QVector<ellipseObject *> &layer, QParallelAnimationGroup &par)
{
    par.clear();
    QVector<QPropertyAnimation*> blinkAnim;
    for(int i = 0; i<layer.size(); i++)
    {
        if(!layer[i]->isActive())
        {m_ref_scene.addItem(layer[i]);}
        blinkAnim.push_back(new QPropertyAnimation(layer[i], "opacity"));
        blinkAnim.last()->setDuration(1000);
        blinkAnim.last()->setStartValue(1);
        blinkAnim.last()->setEndValue(0);
        par.addAnimation(blinkAnim.last());

        connect(&par, &QParallelAnimationGroup::stateChanged, [layer, i](){layer[i]->setVisible(true);});
    }
    connect(&par, &QParallelAnimationGroup::finished, [this](){emit(animationFinished());});
    par.start();
}

void animatedPerceptrone::animateHidenConnections()
{
    animateObject(m_hidenconnections);
}

void animatedPerceptrone::animateOutputConnections()
{
    animateObject(m_outputconnections);
}

void animatedPerceptrone::animateLabels()
{
    m_ref_textEdit.setPlainText("Инициируем веса случайными значениями.");
    animateObject(m_weightsLabel);
}

void animatedPerceptrone::animateSensorLabels()
{
    animateObject(m_sensorsLabel);
}

void animatedPerceptrone::animateFirstNeuronLabels()
{
    animateObject(m_firstNeuronLabel);
}

void animatedPerceptrone::animateSecondNeuronLabels()
{
    animateObject(m_secondNeuronLabel);
}

void animatedPerceptrone::animateOutputNeuronLabels()
{
    animateObject(m_outputNeuronLabel);
}

void animatedPerceptrone::animateLayerLable()
{
    animateObject(m_layerLabel);
}

void animatedPerceptrone::changeFirstNeuronLabels()
{
    m_ref_textEdit.setSource(QUrl("qrc:/res/schema_description/new_weight_first_layer.html"));
    chandeWeightsLabels(0, 4,1);
}

void animatedPerceptrone::changeSecondNeuronLabels()
{
    m_ref_textEdit.setSource(QUrl("qrc:/res/schema_description/new_weight_second_layer.html"));
    chandeWeightsLabels(4, 8,2);
}

void animatedPerceptrone::changeOutputNeuronLabels()
{
    m_ref_textEdit.setSource(QUrl("qrc:/res/schema_description/new_weight_out_layer.html"));
    chandeWeightsLabels(8, 10,3);
}

void animatedPerceptrone::animateSensSignals()
{
    m_ref_textEdit.setSource(QUrl("qrc:/res/schema_description/activation_1_layer.html"));
    animateSensorSignals();
}

void animatedPerceptrone::animateInpSignals()
{
    m_ref_textEdit.setSource(QUrl("qrc:/res/schema_description/activation_2_layer.html"));
    animateSignals(m_hidenSignals, m_hidenconnections, m_blinkHidenLayer, m_parHideBlink, m_parHidSig);
}

void animatedPerceptrone::animateHidSignals()
{
    m_ref_textEdit.setSource(QUrl("qrc:/res/schema_description/activation_out_layer.html"));
    animateSignals(m_outputSignals, m_outputconnections, m_blinkOutputLayer, m_parOutBlink, m_parOutSig);
}

void animatedPerceptrone::animateBackHidSignals()
{
    m_ref_textEdit.setSource(QUrl("qrc:/res/schema_description/dif_out_layer.html"));
    animateSignals(m_backBlinkOutSignals, m_outputconnections, m_blinkHidenLayer, m_parBackBlinkOutSig, m_parBackOutSig, false);
}

void animatedPerceptrone::animateBackInpSignals()
{
    m_ref_textEdit.setSource(QUrl("qrc:/res/schema_description/dif_2_layer.html"));
    animateSignals(m_backBlinkHidSignals, m_hidenconnections, m_blinkInputLayer, m_parBackBlinkInpSig, m_parBackInpSig, false);
}

void animatedPerceptrone::blinkSensConnection()
{
    animateBlinkConnection(m_blinkSensorConnections, m_parBackBlinkSensCon);
    changeFirstNeuronLabels();
}

void animatedPerceptrone::blinkFirstConnection()
{
    animateBlinkConnection(m_blinkhidenconnections, m_parBackBlinkFirstCon);
    changeSecondNeuronLabels();
}

void animatedPerceptrone::blinkSecondConnection()
{
    animateBlinkConnection(m_blinkoutputconnections, m_parBackBlinkSecondCon);
    changeOutputNeuronLabels();
}

void animatedPerceptrone::createConnections(QVector<ellipseObject *> &targetEll, QVector<ellipseObject *> &sourceEll, QVector<lineObject *> &connections, QVector<ellipseObject*> &Signals, QString num, QVector<lineObject*> &blinkconnections)
{
    int c = 0;
    for(int z=0; z<sourceEll.size(); z++)
    {
        for(int i=0; i<targetEll.size(); i++)
        {
            connections.push_back(new lineObject(sourceEll[z]->getX()+sourceEll[z]->getWidth(), sourceEll[z]->getY()+sourceEll[z]->getWidth()/2,
                                                 targetEll[i]->getX(), targetEll[i]->getY()+targetEll[i]->getHeight()/2,Qt::blue));
            m_ref_scene.addItem(connections.last());

            blinkconnections.push_back(new lineObject(sourceEll[z]->getX()+sourceEll[z]->getWidth(), sourceEll[z]->getY()+sourceEll[z]->getWidth()/2,
                                                 targetEll[i]->getX(), targetEll[i]->getY()+targetEll[i]->getHeight()/2,Qt::yellow));
            m_ref_scene.addItem(blinkconnections.last());
            ///создаём метки весов
            m_weightsLabel.push_back(new QGraphicsTextItem("W"+num+", "+QString::number(c+1)));
            m_weightsLabel.last()->setVisible(false);
            m_weightsLabel.last()->setPos(connections.last()->getMiddlePoint());
            m_ref_scene.addItem(m_weightsLabel.last());
            c++;
            ///создайм сигналы
            if(num!="0")
            {
                Signals.push_back(new ellipseObject(connections.last()->getX1(), connections.last()->getY1(), 10, 10 ,Qt::yellow));
                m_ref_scene.addItem(Signals.last());
            }
        }
    }
}

void animatedPerceptrone::createSensorConnections()
{
    int c = 0;
    for(int z=0; z<m_sensors.size(); z++)
    {
        for(int i=0; i<m_inputLayer.size(); i++)
        {
            m_sensorconnections.push_back(new lineObject(m_sensors[z]->getX2(), m_sensors[z]->getY2(),
                                                 m_inputLayer[i]->getX(), m_inputLayer[i]->getY()+m_inputLayer[i]->getHeight()/2,Qt::blue));
            m_ref_scene.addItem(m_sensorconnections.last());


            m_blinkSensorConnections.push_back(new lineObject(m_sensors[z]->getX2(), m_sensors[z]->getY2(),
                                                 m_inputLayer[i]->getX(), m_inputLayer[i]->getY()+m_inputLayer[i]->getHeight()/2,Qt::yellow));
            m_ref_scene.addItem(m_blinkSensorConnections.last());
            ///создаём метки весов
            m_weightsLabel.push_back(new QGraphicsTextItem("W1, "+QString::number(c+1)));
            m_weightsLabel.last()->setVisible(false);
            m_weightsLabel.last()->setPos(m_sensorconnections.last()->getMiddlePoint());
            m_ref_scene.addItem(m_weightsLabel.last());
            c++;
            ///создайм сигналы
            m_sensorSignals.push_back(new ellipseObject(m_sensorconnections.last()->getX1(), m_sensorconnections.last()->getY1(), 10, 10 ,Qt::yellow));
            m_ref_scene.addItem(m_sensorSignals.last());
        }
    }
}

void animatedPerceptrone::createInputLayer()
{
    m_inputLayer.push_back(new ellipseObject(w/12*3, h/3, 50, 50, Qt::red));
//    m_inputLayer.push_back(new ellipseObject(w/6, (h/3)*2, 50, 50, Qt::red));
    m_inputLayer.push_back(new ellipseObject(w/12*3, (h/3)*2, 50, 50, Qt::red));

    m_blinkInputLayer.push_back(new ellipseObject(w/12*3, h/3, 50, 50, Qt::yellow));
//    m_blinkInputLayer.push_back(new ellipseObject(w/6, (h/3)*2, 50, 50, Qt::yellow));
    m_blinkInputLayer.push_back(new ellipseObject(w/12*3, (h/3)*2, 50, 50, Qt::yellow));

    m_firstNeuronLabel.push_back(new QGraphicsTextItem("F1"));
    m_firstNeuronLabel.last()->setVisible(false);
    m_firstNeuronLabel.last()->setPos(w/12*3+12, h/3+12);

    m_firstNeuronLabel.push_back(new QGraphicsTextItem("F2"));
    m_firstNeuronLabel.last()->setVisible(false);
    m_firstNeuronLabel.last()->setPos(w/12*3+12, (h/3)*2+12);

}

void animatedPerceptrone::createHidenLayer()
{
    m_hidenLayer.push_back(new ellipseObject(w/12*6, (h/3), 50, 50, Qt::red));
//    m_hidenLayer.push_back(new ellipseObject(w, (h/3)*2, 50, 50, Qt::red));
    m_hidenLayer.push_back(new ellipseObject(w/12*6, (h/3)*2, 50, 50, Qt::red));
//    m_hidenLayer.push_back(new ellipseObject(w, (h/3)*4, 50, 50, Qt::red));

    m_blinkHidenLayer.push_back(new ellipseObject(w/12*6, (h/3), 50, 50, Qt::yellow));
//    m_blinkHidenLayer.push_back(new ellipseObject(w, (h/3)*2, 50, 50, Qt::yellow));
    m_blinkHidenLayer.push_back(new ellipseObject(w/12*6, (h/3)*2, 50, 50, Qt::yellow));
//    m_blinkHidenLayer.push_back(new ellipseObject(w, (h/3)*4, 50, 50, Qt::yellow));

    m_secondNeuronLabel.push_back(new QGraphicsTextItem("F3"));
    m_secondNeuronLabel.last()->setVisible(false);
    m_secondNeuronLabel.last()->setPos(w/12*6+12, (h/3)+12);

    m_secondNeuronLabel.push_back(new QGraphicsTextItem("F4"));
    m_secondNeuronLabel.last()->setVisible(false);
    m_secondNeuronLabel.last()->setPos(w/12*6+12, (h/3)*2+12);
}

void animatedPerceptrone::createOutputLayer()
{
//    m_outputLayer.push_back(new ellipseObject((w/6)*7, h/3, 50, 50, Qt::red));
    m_outputLayer.push_back(new ellipseObject(w/12*9, (h/3)*1.5, 50, 50, Qt::red));
//    m_outputLayer.push_back(new ellipseObject((w/6)*7, (h/3)*3, 50, 50, Qt::red));

//    m_blinkOutputLayer.push_back(new ellipseObject((w/6)*7, h/3, 50, 50, Qt::yellow));
    m_blinkOutputLayer.push_back(new ellipseObject(w/12*9, (h/3)*1.5, 50, 50, Qt::yellow));
//    m_blinkOutputLayer.push_back(new ellipseObject((w/6)*7, (h/3)*3, 50, 50, Qt::yellow));

    m_outputNeuronLabel.push_back(new QGraphicsTextItem("F5"));
    m_outputNeuronLabel.last()->setVisible(false);
    m_outputNeuronLabel.last()->setPos(w/12*9+12, (h/3)*1.5+12);
}

template<typename T>
void animatedPerceptrone::animateObject(QVector<T*> obj)
{
    m_par.clear();
    QVector<QPropertyAnimation*> inpAnim;
    for(int z=0; z<obj.size(); z++)
    {
        if(!obj[z]->isActive())
        {m_ref_scene.addItem(obj[z]);}
        inpAnim.push_back(new QPropertyAnimation(obj[z], "scale"));
        inpAnim.last()->setDuration(1000);

        if(animateFlag)
        {
            inpAnim.last()->setStartValue(0);
            inpAnim.last()->setEndValue(1);
        }
        else
        {
            inpAnim.last()->setStartValue(1);
            inpAnim.last()->setEndValue(0);
        }
        m_par.addAnimation(inpAnim.last());
        connect(&m_par, &QParallelAnimationGroup::stateChanged, [obj, z]()
        {
            obj[z]->setVisible(true);
        });
    }
    connect(&m_par, &QParallelAnimationGroup::finished, [this](){emit(animationFinished());});
    m_par.start();
}
