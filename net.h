#ifndef NET_H
#define NET_H

#include "neuron.h"

struct Example
{
  QString path;
  QString answer;
};

class net : public QObject
{
  Q_OBJECT
private:
    //std::vector<neuron> layer;
    std::vector<std::vector<neuron > > m_neural_net;   //neural_net[layer_num][num_of_neurons]
    std::vector<std::vector<double > > m_weights;
    void calcActivation (std::vector<double> &inp_vals);
    void calcErrors (const  int &answer);
    void adjustWeights ();
    void check(const int &answer); //преверяет распознавание
    void setLearnSpeed(double learn_speed);
    int guess();
    int m_errors = 0, m_correct = 0, m_counter = 0;
    double m_learn_speed;

    void createNet(const std::vector<int> &topology);
    void learnNet(std::map<QString, QString> &examples);
    void testNet(std::vector<Example> &examples);

    void learnNetTEST(std::vector<Example> &examples, int num_epochs=1);

    //test
    void adjustWeightsTest (std::vector<double> &inp_vals);
    QVector<double> m_correct_data; //количество правильно распознанных
    QVector<double> m_incorrect_data; //количество неправильно распознанных

public:
    explicit net(QObject* parent =nullptr);
    ~net();

    void createNet(const std::vector<std::vector<neuron>> &net);
    std::vector<std::vector<neuron > > getNet();
    std::vector<std::vector<double > > getWeights();
    int recognize(const QImage &img);

    int &getError();
    int &getCorrect();
    int &getCounter();
    QVector<double>& getCorrectData();
    QVector<double>& getInCorrectData();


public slots:
    void startLearn(const std::vector<int> &topology, std::vector<Example> &examples, int num_epochs, double learn_speed, std::vector<Example> &test);

public: signals:
    void netIsLearned();

};

#endif // NET_H
