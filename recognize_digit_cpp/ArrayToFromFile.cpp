
#include "stdafx.h"
#include "ArrayToFromFile.h"

using namespace std;

 void ArrayToFromFile::VecToFile(std::vector<std::vector<int>> blackwhitevec,  int x, int y)
{
    ofstream f;
    f.open("weiguts.txt");
    int t = x + 2;
    //using index_t = std::vector<int>::size_type;
    if (f.is_open()) {
        for (int i = 0; i < t; i++)
        {
            //запись размеров вектора-------
            if (i == 0) { f << y << "\n"; i++; f << x << "\n"; i++; }
            //if (i == 1 && i != 0) { f << x << "\n"; i++; }
            //------------------------------
            if (i>=3){ f << "\n"; }
            //if (i == 0)
            //{
            //	f << y << " " << x;//попробуем записать размер вектора в файл перво строкой,
            //					   //чтобы можно было восстанавливать картины разных размеров
            //}
            //f << "\n";
            for (int j = 0; j < y; j++)
            {
                f << blackwhitevec[static_cast<std::vector<int>::size_type>(i)-2][static_cast<std::vector<int>::size_type>(j)];
            }
        }
    }
    f.close();
}

 void ArrayToFromFile::SingleVecToFile(std::vector<int> weights)
 {
     ofstream f;
     f.open("weiguts.txt");
     if (f.is_open()) {
         for (int i = 0; i < static_cast<int>(weights.capacity());  i++)
         {
                 f << weights[static_cast<std::vector<int>::size_type>(i)] << "\n";
         }
     }
     f.close();
 }

 void ArrayToFromFile::SingleVecToFileTest(std::vector<int> weights)
 {
     ofstream f;
     f.open("testmatr.txt");
     if (f.is_open()) {
         for (int i = 0; static_cast<std::vector<int>::size_type>(i) < weights.capacity(); i++)
         {
             f << weights[static_cast<std::vector<int>::size_type>(i)] << "\n";
         }
     }
     f.close();
 }

 void ArrayToFromFile::ArrayToFile(int ** arr, int column, int row, std::string name)
 {
     ofstream f;
     f.open(name);
     int t = column + 2;
     if (f.is_open()) {
         for (int i = 0; i < t; i++)
         {
             //запись размеров вектора-------
             if (i == 0) { f << row << "\n"; i++; f << column << "\n"; i++; }
             //if (i == 1 && i != 0) { f << x << "\n"; i++; }
             //------------------------------
             if (i >= 3) { f << "\n"; }
             //if (i == 0)
             //{
             //	f << y << " " << x;//попробуем записать размер вектора в файл перво строкой,
             //					   //чтобы можно было восстанавливать картины разных размеров
             //}
             //f << "\n";
             for (int j = 0; j < row; j++)
             {
                 f << arr[i - 2][j]<<';';
             }
         }
     }
     f.close();
 }

 void ArrayToFromFile::Avg_VecToFile(std::vector<std::vector<int>> Sum_Avg_Vec)
 {
     ofstream f;
     f.open("AVG.txt");
     unsigned long long t = Sum_Avg_Vec.size() + 2;
     if (f.is_open()) {
         for (unsigned long long i = 0; i < t; i++)
         {
             //запись размеров вектора-------
             if (i == 0) { f << Sum_Avg_Vec.size() << "\n"; i++; f << Sum_Avg_Vec.size(); i++; }
             //if (i == 1 && i != 0) { f << x << "\n"; i++; }
             //------------------------------
            // if (i >= 3) { f << "\n"; }
             //if (i == 0)
             //{
             //	f << y << " " << x;//попробуем записать размер вектора в файл перво строкой,
             //					   //чтобы можно было восстанавливать картины разных размеров
             //}
             //f << "\n";
             for (unsigned long long j = 0; j < Sum_Avg_Vec.size(); j++)
             {
                 f << "\n" << Sum_Avg_Vec[i - 2][j];
             }
         }
     }
     f.close();
 }

 std::vector<std::vector<int>> ArrayToFromFile::Avg_FileToVec(std::ifstream & ff)
 {
    // ifstream in;
     //in.open("AVG.txt");//открываем файл для вывода инфы из файла в прогу
     //char dig;//символ в файле, может принимать значенио 0 или 1 или размер вектора
     signed int x=0, y=0;//размеры вектора
     string str;//переменная для записи числа()
     if (!ff.is_open()) // если файл не открыт
         cout << "Файл не может быть открыт!\n"; // сообщить об этом
     else
     {
         //узнаём размеры вектора из файла------------
         for (int f = 0; f < 2; f++)//это цикл для пробега по 2 первым строкам в файле(эти строки хранят размерность вектора)
         {
             str = "";
             while (getline(ff, str)) {
                 str = str;
                 break;
             }
             if (f == 0) { y = std::stoi(str); }//из символов получаем строку и конвертируем в число
             if (f == 1) { x = std::stoi(str); }
         }
         vector<vector<int>> output_avg(x, vector <int>(y));//получив размер вектора создаём его
                                                               //-------------------------------------------
         int t = x + 2;//для ограничителя
         for (int i = 2; i < t; i++)//игнорим 2 первые строки, так как они задают размер вектора
         {
             for (int j = 0; j < y; j++)
             {
                 str = "";
                 while (getline(ff, str)) {
                     str = str;
                     break;
                 }
                 output_avg[i - 2][j] = std::stoi(str);
             }
         }
         ff.close(); // закрываем файл
         return output_avg;
     }
 }

 int **ArrayToFromFile::LoadWeights(std::ifstream& in)
 {
//     ifstream in;
//     in.open(filename);//открываем файл для вывода инфы из файла в прогу
     std::string str;//переменная для записи числа()
     if (!in.is_open()) // если файл не открыт
     {}
        // QMessageBox::critical(this, "Файл не найден!", "Файл с весами не найден!");
         //QMessage::Show("Файл с весами для цифры \"1\" не найден!"); // сообщить об этом
     else
     {
         char dig;//символ в файле
         bool isNeg = false;//является ли число отрицательным

         //узнаём размеры из файла--------------------
         for (int f = 0; f < 2; f++)//это цикл для пробега по 2 первым строкам в файле(эти строки хранят размерность)
         {
             getline(in, str);
             if (f == 0) { columns = static_cast<size_t>(std::stoi(str)); }//из символов получаем строку и конвертируем в число
             if (f == 1) { rows = static_cast<size_t>(std::stoi(str)); }
         }

         load_weights = new int* [rows];


         //-------------------------------------------
         for (size_t i = 2; i < rows + 2; i++)//игнорим 2 первые строки, так как они задают размер
         {
             load_weights[i - 2] = new int[columns];
             for (size_t j = 0; j < columns; j++)
             {
                 str = "";
                 isNeg = false;
                 in >> dig;
                 while (dig != ';' && dig != '\n')
                 {
                     if (dig == '-')
                     {
                         isNeg = true;
                     }
                     else
                     {
                         str += dig;
                     }
                     in >> dig;
                 }
                 if (isNeg)
                 {
                    load_weights[i - 2][j] = 0 - std::stoi(str);
                 }
                 else
                 {
                     load_weights[i - 2][j] = std::stoi(str);
                 }
             }
         }
         in.close(); // закрываем файл
     }
     return load_weights;
 }

 size_t &ArrayToFromFile::GetRows()
 {
     return rows;
 }

 size_t &ArrayToFromFile::GetColumns()
 {
     return columns;
 }

 int ** ArrayToFromFile::FileToArray(std::ifstream & f)
 {
     ifstream in;
     in.open("weiguts.txt");//открываем файл для вывода инфы из файла в прогу
     char dig;//символ в файле, может принимать значенио 0 или 1 или размер вектора
     int x=0, y=0;//размеры вектора
     string str;//переменная для записи числа()
     if (!in.is_open()) // если файл не открыт
         cout << "Файл не может быть открыт!\n"; // сообщить об этом
     else
     {
         //узнаём размеры вектора из файла------------
         for (int f = 0; f < 2; f++)//это цикл для пробега по 2 первым строкам в файле(эти строки хранят размерность вектора)
         {
             str = "";
             while (getline(in, str)) {
                 str = str;
                 break;
             }
             if (f == 0) { y = std::stoi(str);; }//из символов получаем строку и конвертируем в число
             if (f == 1) { x = std::stoi(str); }
         }
         int ** arr = new int *[x];//получив размер вектора создаём его
         //-------------------------------------------
         int t = x + 2;//для ограничителя
         for (int i = 2; i < t; i++)//игнорим 2 первые строки, так как они задают размер вектора
         {
             arr[i] = new int[y];
             for (int j = 0; j < y; j++)
             {
                 in >> dig;
                 arr[i - 2][j] = static_cast<int>(dig);
             }
         }
         in.close(); // закрываем файл
         return arr;
     }
 }

 void ArrayToFromFile::WriteWeights(int **arr, QImage &img, char const *name)
 {
     ofstream f;
     f.open(name);
     int t = img.height() + 2;
     if (f.is_open()) {
         for (int i = 0; i < t; i++)
         {
             //запись размеров массива-------
             if (i == 0) { f << img.height() << "\n"; i++; f << img.width() << "\n"; i++; }
             //------------------------------
             if (i >= 3) { f << "\n"; }
             for (int j = 0; j < img.width(); j++)
             {
                 f << arr[i - 2][j]<<';';
             }
         }
     }
     f.close();
 }

 void ArrayToFromFile::SaveNueralNetwork(std::vector<std::vector<neuron> > &inp_net)
 {
     ofstream f;
     std::vector<double> tmp;
     f.open("neural_network.txt");
     for (size_t i = 0; i<inp_net.size(); i++)
     {
         f <<"Layer"<< "\n";
         for (size_t j = 0; j<inp_net[i].size(); j++)
         {
             f <<"Neuron"<< "\n";
             tmp = inp_net[i][j].neuron::getWeight();
             for (size_t z = 0; z<tmp.size(); z++)
             {
                 f <<tmp[z]<<";";
             }
             f << "\n";
         }
     }
     f.close();
 }

 std::vector<std::vector<neuron> > ArrayToFromFile::LoadNetwork()
 {
     ifstream in;
     in.open("neural_network.txt");
     std::string str;//переменная для записи числа()
     std::string tmp_str;
     std::vector<std::vector<neuron> > tmp;
     int neuron_cnt=0, layer_count = 0;
     if (!in.is_open()) // если файл не открыт
     {}
        // QMessageBox::critical(this, "Файл не найден!", "Файл с весами не найден!");
         //QMessage::Show("Файл с весами для цифры \"1\" не найден!"); // сообщить об этом
     else
     {
         char dig;//символ в файле
         bool isNeg = false;//является ли число отрицательным

         while (getline(in, str))
         {
             if(str == "Layer")
             {
                 tmp.push_back(std::vector<neuron>());
                 layer_count++;
                 neuron_cnt = 0;
             }
             else if(str == "Neuron")
             {
                 tmp.at(static_cast<size_t>(layer_count-1)).push_back(neuron());
                 neuron_cnt++;
             }
             else         
             {
              tmp_str = ""; //временная строка в которую записываем число из файла
              isNeg = false; //индикатор знака числа: положительное или отрицательное
                 for (size_t i=0; i<str.length(); i++)
                 {
                     dig=str[i];
                     if(dig!=';')
                     {
                         if(dig=='-')
                         {
                             isNeg=true;
                         }
                         else
                         {
                            tmp_str += dig;
                         }
                     }
                     else
                     {
                         if (isNeg)
                         {
                            //cout << tmp_str<<" num - " <<dig<< "\n";
                            tmp.at(static_cast<size_t>(layer_count-1)).at(static_cast<size_t>(neuron_cnt-1)).setWeight( 0 - std::stod(tmp_str));
                            tmp_str = "";
                            isNeg = false;

                         }
                         else
                         {
                            //cout << tmp_str<<" num - "<<dig << "\n";
                            tmp.at(static_cast<size_t>(layer_count-1)).at(static_cast<size_t>(neuron_cnt-1)).setWeight(std::stod(tmp_str));
                            tmp_str = "";
                         }
                     }
                 }
             }
         }
         in.close(); // закрываем файл
     }
     return tmp;
 }

// void ArrayToFromFile::WriteWeights(std::vector<std::vector<double> > &inp_vec, char const *name)
// {
//     ofstream f;
//     f.open(name);
//     size_t t = inp_vec.size() + 2;
//     if (f.is_open()) {
//         for (size_t i = 0; i < t; i++)
//         {
//             //запись размеров массива-------
//             if (i == 0) { f << inp_vec.size() << "\n"; i++; f << inp_vec.at(0).size() << "\n"; i++; }
//             //------------------------------
//             if (i >= 3) { f << "\n"; }
//             for (size_t j = 0; j < img.width(); j++)
//             {
//                 f << arr[i - 2][j]<<';';
//             }
//         }
//     }
//     f.close();
// }

 std::vector<std::vector<int>> ArrayToFromFile::FileToVec(std::ifstream &f)
 {
     ifstream in;
     in.open("weiguts.txt");//открываем файл для вывода инфы из файла в прогу
     char dig;//символ в файле, может принимать значенио 0 или 1 или размер вектора
     unsigned long long x, y;//размеры вектора
     string str;//переменная для записи числа()
     if (!in.is_open()) // если файл не открыт
         cout << "Файл не может быть открыт!\n"; // сообщить об этом
     else
     {
         //узнаём размеры вектора из файла------------
         for (int f = 0; f < 2; f++)//это цикл для пробега по 2 первым строкам в файле(эти строки хранят размерность вектора)
         {
             str = "";
             while (getline(in, str)) {
                 str = str;
                 break;
             }
                     if (f == 0) {  y = std::stoi(str); }//из символов получаем строку и конвертируем в число
                     if (f == 1) {  x = std::stoi(str); }
         }
         vector<vector<int>> blackwhitevec(x, vector <int>(y));//получив размер вектора создаём его
         //-------------------------------------------
         int t = x + 2;//для ограничителя
         for (int i = 2; i < t; i++)//игнорим 2 первые строки, так как они задают размер вектора
         {
             for (int j = 0; j < y; j++)
             {
                 in >> dig;
                 blackwhitevec[static_cast<std::vector<int>::size_type>(i)-2][static_cast<std::vector<int>::size_type>(j)]= static_cast<int>(dig);
             }
         }
         in.close(); // закрываем файл
         return blackwhitevec;
     }
 }

ArrayToFromFile::ArrayToFromFile()
{
}

ArrayToFromFile::~ArrayToFromFile()
{
}
