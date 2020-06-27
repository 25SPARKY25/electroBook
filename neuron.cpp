#include "neuron.h"

neuron::neuron()
{

}

neuron::neuron(double learn_speed)
{
    this->m_learn_speed = learn_speed;
}

void neuron::setRandWeights(const int &next_number_neurons)
{
 srand( static_cast<unsigned int>(time(0)));
    for (size_t i=0; i<static_cast<size_t>(next_number_neurons); i++)
    {

        m_weights.push_back(  (double)rand()/RAND_MAX );
    }
}

void neuron::setWeight(const double &weight)
{
    m_weights.push_back(weight);
}

 std::vector<double> neuron::getWeight()
{
     return this->m_weights;
 }

 double neuron::calcSum(std::vector<double> &inp_values)
 {
     double sum = 0;

     for (std::size_t i =0; i <inp_values.size(); i++)
     {
         sum+=inp_values.at(i) * this->m_weights.at(i);
     }
     return sum;
 }

 void neuron::activate(double sum)
 {
     m_activated_val = 0; //обнуление
     m_activated_val = 1/(1+exp(-sum));
 }

 double neuron::getActivatedVal()
 {
     return m_activated_val;
 }

 double neuron::calcOutpError(unsigned short answer)
 {
        m_error = 0; //обнуляем предыдущее значение
     return m_error = answer-m_activated_val;
 }

 double neuron::getError()
 {
     return m_error;
 }

 void neuron::calcHidenError(const std::vector<double> &errors, const std::vector<std::vector<double> > &inp_weights, const size_t &index)
 {
     m_error = 0; //обнуляем предыдущее значение
     std::vector<double> sum(errors.size(), 0); //сумма по строкам матрицы весов inp_weights
     for (std::size_t i = 0; i < inp_weights.size(); i++) //циклы подсчёта суммы по столбцам
     {
         for (std::size_t j = 0; j < inp_weights[i].size(); j++)
         {
            sum.at(i)+= inp_weights[i][j];
         }
         m_error+= errors.at(i) * inp_weights.at(i).at(index) / sum.at(i);
     }
 }

 void neuron::calcHidenErrorTest(const std::vector<double> &errors, const std::vector<std::vector<double> > &inp_weights, const size_t &index)
 {
     //index - это номер нейрона для которого вычисляется ошибка
  m_error = 0;

  for (size_t i = 0; i < errors.size(); i++)
  {
     m_error +=errors.at(i)*inp_weights.at(i).at(index);
  }

 }

 void neuron::adjustWeightsTest(const std::vector<double> &inp_vals)
 {
     for (size_t i = 0; i < inp_vals.size(); i++)
     {
         m_weights.at(i) = m_weights.at(i) + m_error * (m_activated_val*(1-m_activated_val)) *inp_vals.at(i) * m_learn_speed;
     }
 }
