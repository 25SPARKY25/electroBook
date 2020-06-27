#ifndef NEURON_H
#define NEURON_H

class neuron
{
private:
    std::vector<double> m_weights;
    double m_activated_val;
    double m_error;
    double m_learn_speed;
    //double sum;
public:
    neuron();
    neuron(double learn_speed);
    void setRandWeights(const int &next_number_neurons);
    void setWeight(const double &weight);
    std::vector<double> getWeight();
    double calcSum(std::vector<double> &inp_values); //для подсчёта первого скрытого слоя
    void calcSumForAdjust(); //для суммы вычисления влияния веса
    void activate(double sum);
    double getActivatedVal();
    double calcOutpError(unsigned short int answer); //подсчёт ошибки нейрона выходного слоя
    double getError(); //получение ошибки
    void calcHidenError(const std::vector<double> &errors, const std::vector<std::vector<double>> &inp_weights, const size_t &index); //подсчёт ошибки во внутреннем слое
    void adjustWeights(); //корректировка весов


    //test
    void calcHidenErrorTest(const std::vector<double> &errors, const std::vector<std::vector<double>> &inp_weights, const size_t &index); //подсчёт ошибки во внутреннем слое
    void adjustWeightsTest(const std::vector<double> &inp_vals); //корректировка весов

};

#endif // NEURON_H
