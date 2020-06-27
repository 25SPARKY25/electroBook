#include "recognize_digit_cpp/stdafx.h"
#include "recognize_digit_cpp/ImageToArray.h"
#include "recognize_digit_cpp/ArrayToFromFile.h"
#include "net.h"

void net::calcActivation( std::vector<double> &inp_vals )
{
    std::vector<double> activated_vals; //вектор значений активации нейронов
    //цикл по прогону обучающей картинки по сети и расчёта ошибки выходгого слоя
    for(std::size_t i = 0; i < m_neural_net.size(); i++) //цикл пробежки по слоям сети
    {
        if(i == 0) //если это слой после входного, то скармливаем картинку второму слою(скрытому)
        {
            for (std::size_t j = 0;  j < m_neural_net[i].size(); j++) //цикл пробежки по нейронам второго слоя(скрытого)
            {
                m_neural_net[i][j].activate( m_neural_net[i][j].calcSum(inp_vals) );
            }
        }

        else
        {           
            for (size_t j = 0; j<m_neural_net.at(i-1).size(); j++)
            {
                activated_vals.push_back(m_neural_net[i-1][j].getActivatedVal()); //записываем значения активации нейронов прошлого слоя
            }

            for (size_t z = 0; z<m_neural_net.at(i).size(); z++)
            {
                m_neural_net[i][z].activate(m_neural_net[i][z].calcSum( activated_vals ));
            }
            activated_vals.clear();
        }
    }
}

void net::calcErrors(const  int &answer)
{
    std::vector<double> error_vector; //вектор ошибок слоя
    std::vector<std::vector<double>> weights_vector; //вектор весов для расчёта ошибки скрытого слоя
    //цикл по расчёту ошибки скрытых слоёв и корректировки весов
    for (std::size_t i = (m_neural_net.size()-1); static_cast<int>(i) > -1 ; i--) //цикл пробежки по слоям сети, кроме первого
    {
        //если это внешний слой то посчитаем выходную ошибку
        if (i == (m_neural_net.size()-1))
        {
            for (std::size_t j = 0; j<m_neural_net[i].size(); j++) //цикл пробежки по нейронам в слое
            {
                if(j == static_cast<std::size_t>(answer) )
                {
                    m_neural_net[i][j].calcOutpError(1);
                }
                else
                {
                    m_neural_net[i][j].calcOutpError(0);
                }
                error_vector.push_back(m_neural_net[i][j].getError());
                weights_vector.push_back(m_neural_net[i][j].getWeight());
            }
        }
        else
        {
            for (std::size_t j = 0; j<m_neural_net[i].size(); j++) //цикл пробежки по нейронам в слое
            {
                m_neural_net[i][j].calcHidenErrorTest(error_vector, weights_vector, j);
            }

            error_vector.clear();
            weights_vector.clear();
            if (i!=0) //если это не первый слой
            {
                for (std::size_t j = 0; j<m_neural_net[i].size(); j++) //цикл пробежки по нейронам в слое
                {
                    error_vector.push_back(m_neural_net[i][j].getError());
                    weights_vector.push_back(m_neural_net[i][j].getWeight());
                }
            }
        }
    }
}

void net::adjustWeights()
{
    for (size_t i = 0; i < m_neural_net.size(); i++)
    {
        for (std::size_t j = 0; j<m_neural_net[i].size(); j++) //цикл пробежки по нейронам в слое
        {
            //            neural_net.at(i).at(j).adjustWeights();
        }
    }
}

void net::check(const  int &answer)
{
    int max_index = 0; //для поиска маскимума
    double tmp = 0; //для поиска маскимума
    //смотрим угадала ли число нейронка
    max_index = 0;
    tmp = m_neural_net[(m_neural_net.size()-1)][0].getActivatedVal();
    for (size_t max_ind = 1; max_ind < m_neural_net[(m_neural_net.size()-1)].size(); max_ind++)
    {
        if( tmp <= m_neural_net[(m_neural_net.size()-1)][max_ind].getActivatedVal() )
        {
            max_index = static_cast<int>(max_ind);
            tmp = m_neural_net[(m_neural_net.size()-1)][max_ind].getActivatedVal();
        }
    }

    if(max_index!= answer)
    {
        m_errors++;
        m_incorrect_data[max_index]++;
    }
    else
    {
        m_correct++;
        m_correct_data[max_index]++;
    }

    m_counter++;
    //double perc=(static_cast<double>(correct)/static_cast<double>(counter) *100.0);
    //            std::cout<< "Number of file - " <<counter<<endl;
    //            std::cout<< "Number of errors - " <<errors<<endl;
    //            std::cout<< "Number of correct - " <<correct<<endl;
    //            std::cout<< "Example - " <<answer<<endl;
    //            std::cout<< "Predict - " <<max_index<<endl;
    //            std::cout<< "% of Correct - " <<(static_cast<double>(correct)/static_cast<double>(counter) *100.0)<<"%" <<endl;
}

void net::setLearnSpeed(double learn_speed)
{
    this->m_learn_speed=learn_speed;
}

int net::guess()
{
    int max_index = 0; //для поиска маскимума
    double tmp = 0; //для поиска маскимума
    //смотрим угадала ли число нейронка
    max_index = 0;
    tmp = m_neural_net[(m_neural_net.size()-1)][0].getActivatedVal();
    for (size_t max_ind = 1; max_ind < m_neural_net[(m_neural_net.size()-1)].size(); max_ind++)
    {
        if( tmp <= m_neural_net[(m_neural_net.size()-1)][max_ind].getActivatedVal() )
        {
            max_index = static_cast<int>(max_ind);
            tmp = m_neural_net[(m_neural_net.size()-1)][max_ind].getActivatedVal();
        }
    }
    return max_index;
}

void net::adjustWeightsTest(std::vector<double> &inp_vals)
{
    for (size_t i = 0; i < m_neural_net.size(); i++)
    {
        if(i==0)
        {
            for (std::size_t j = 0; j<m_neural_net[i].size(); j++) //цикл пробежки по нейронам в слое
            {
                m_neural_net.at(i).at(j).adjustWeightsTest(inp_vals);
            }
        }
        else
        {
            inp_vals.clear();
            for (std::size_t j = 0; j<m_neural_net[i-1].size(); j++) //цикл пробежки по нейронам в слое
            {
                inp_vals.push_back( m_neural_net.at(i-1).at(j).getActivatedVal() );
            }
            for (std::size_t j = 0; j<m_neural_net[i].size(); j++) //цикл пробежки по нейронам в слое
            {
                m_neural_net.at(i).at(j).adjustWeightsTest(inp_vals);
            }
        }

    }
}

void net::createNet(const std::vector<int> &topology)
{
    srand( static_cast<unsigned int>(time(0)));
    for (size_t i = 1; i<topology.size(); i++) //начинаем создание сразу со скрытых слоёв, ибо веса привязаны к нейронам последующих слоёв, т.е. у нейронов входного слоя ничего нету
    {
        m_neural_net.push_back(std::vector<neuron>()); //создаём слои
        for (size_t j = 0; j < static_cast<size_t>(topology[i]) ; j++)
        {
            m_neural_net[i-1].push_back(neuron(m_learn_speed)); // создаём нейрон

            for (size_t z = 0; z < static_cast<size_t>(topology[i-1]) ; z++)
            {
                m_neural_net[i-1][j].setWeight( (double)rand()/RAND_MAX - (double)rand()/RAND_MAX);
            }
        }
    }
}

void net::createNet(const std::vector<std::vector<neuron> > &net)
{
    m_neural_net = net;
}

net::net(QObject* parent) : QObject(parent), m_correct_data(10, 0.0), m_incorrect_data(10, 0.0)
{}

net::~net()
{
//    delete this;
}

std::vector<std::vector<neuron > > net::getNet()
{
    return m_neural_net;
}

std::vector<std::vector<double> > net::getWeights()
{
    return this->m_weights;
}

int net::recognize(const QImage &img)
{
    std::vector<double> inp_vals; //вектор входных значений
    inp_vals = ImageToArray::BWImageToVector(img);

    calcActivation(inp_vals);
    return guess();
}

void net::learnNet(std::map<QString, QString> &examples)
{
    QImage img;
    std::vector<double> inp_vals; //вектор входных значений
    m_errors = 0;
    m_correct = 0;
    m_counter = 0;
    for (std::map<QString, QString>::iterator it = examples.begin(); it != examples.end(); ++it) //цикл пробежки по обучающей выборке
    {
        img = QImage(it->first); //получаем картинку из файла
        ImageToArray::getBoldImage(img);
        inp_vals = ImageToArray::BWImageToVector(img);
        calcActivation(inp_vals);
        check(it->second.toInt());
        calcErrors(it->second.toInt());
        adjustWeights();
    }
    ArrayToFromFile::SaveNueralNetwork(m_neural_net);
}

void net::testNet(std::vector<Example> &examples)
{
    emit netIsLearned();
    QImage img;
    std::vector<double> inp_vals; //вектор входных значений
    m_errors = 0;
    m_correct = 0;
    m_counter = 0;

    srand( static_cast<unsigned int>(time(0)));
    int rand_index;

    std::cout<<"Starting test"<<endl;

        for (size_t it = 0; it < examples.size(); ) //цикл пробежки по обучающей выборке
        {
            static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
            rand_index = static_cast<int>(rand() * fraction * (examples.size() -0) + 0);
            img = QImage(examples.at(static_cast<size_t>(rand_index) ).path); //получаем картинку из файла
            ImageToArray::getBoldImage(img);
            inp_vals = ImageToArray::BWImageToVector(img);
            calcActivation(inp_vals);
            check(examples.at(static_cast<size_t>(rand_index)).answer.toInt());
            examples.erase(examples.begin()+rand_index);
        }
        examples.clear();

    std::cout<<"Done"<<endl;
}

void net::learnNetTEST(std::vector<Example> &examples, int num_epochs)
{
    QImage img;
    std::vector<double> inp_vals; //вектор входных значений
    m_errors = 0;
    m_correct = 0;
    m_counter = 0;
    srand( static_cast<unsigned int>(time(0)));
    int rand_index;

    std::vector<Example> tmp;
    std::cout<<"Starting learn"<<endl;
    for (int i = 0; i<num_epochs; i++)
    {
        tmp = examples;
        for (size_t it = 0; it < tmp.size(); ) //цикл пробежки по обучающей выборке
        {
            static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
            rand_index = static_cast<int>(rand() * fraction * (tmp.size() -0) + 0);
            img = QImage(tmp.at(static_cast<size_t>(rand_index) ).path); //получаем картинку из файла
            ImageToArray::getBoldImage(img);
            inp_vals = ImageToArray::BWImageToVector(img);
            calcActivation(inp_vals);
            check(tmp.at(static_cast<size_t>(rand_index)).answer.toInt());
            calcErrors(tmp.at(static_cast<size_t>(rand_index)).answer.toInt());
            adjustWeightsTest(inp_vals);
            tmp.erase(tmp.begin()+rand_index);
        }
        tmp.clear();
        std::cout<<"Epoch - "<<i<<endl;
    }
    std::cout<<"Done"<<endl;
    ArrayToFromFile::SaveNueralNetwork(m_neural_net);
}

int &net::getError()
{
    return m_errors;
}

int &net::getCorrect()
{
    return m_correct;
}

int &net::getCounter()
{
    return m_counter;
}

QVector<double> &net::getCorrectData()
{
    return m_correct_data;
}

QVector<double> &net::getInCorrectData()
{
    return m_incorrect_data;
}


void net::startLearn(const std::vector<int> &topology, std::vector<Example> &examples, int num_epochs, double learn_speed, std::vector<Example> &test)
{
    setLearnSpeed(learn_speed);
    createNet(topology);
    learnNetTEST(examples, num_epochs);
    testNet(test);
}

