#include <iostream>
#include "BoxMullerTransform.h"
#include "Prim.h"
#include "HamiltonianCycleApproximationMST.h"
#include "HamiltonianCycleExhaustiveSearch.h"
using namespace std;

int main() 
{
    int experimentsCount = 0; 
    cout << "Turn number of experiments" << endl;
    cin >> experimentsCount;
    int verticesCount = 0;
    cout << "Turn number of points" << endl;
    cin >> verticesCount;
    vector <double> difference( experimentsCount, 0 ); // Вектор разностей нашего и лучшего ответа на каждом тесте.
    double sumOfAll = 0; // Сумма всех отклонений.
    for( int i = 0; i < experimentsCount; ++i ) {
        CBoxMullerTransform DistributionClass( verticesCount ); // Класс для создания нормального распределения точек.
        DistributionClass.generateNormalDistribution();
        vector<CBoxMullerTransform::Point> distribution = DistributionClass.getVectorDistribution();
        /*
        for( int i = 0; i < verticesCount; ++i ) // Вывод точек.
            cout << distribution[i].x << ' ' << distribution[i].y << endl;*/
        const double infinity = 1000000000;
        // Строим полный граф по точкам.
        vector < vector<double> > graph( verticesCount, vector<double>( verticesCount, infinity ) );
        for( int i = 0; i < verticesCount; ++i )
            for( int j = 0; j < verticesCount; ++j ) {
                graph[i][j] = distribution[i].getDistance( distribution[j] );
            }
        CPrim solvingClass( verticesCount, graph ); // Класс находящий MST алгоритмом Прима.
        solvingClass.solveMST();
        vector< vector<int> > MST = solvingClass.getMST();
        /*for( int i = 0; i < verticesCount - 1; ++i ) // Вывод MST
            for( int j = 0; j < MST[i].size(); ++j )
                cout << i << ' ' << MST[i][j] << endl;*/
        double MSTlen = solvingClass.getMSTlen();
        cout << "MST length: " << MSTlen << endl;
        cout << endl;
        // Аппроксимация задачи коммиваяжера с помощью MST.
        CHamiltonianCycleApproximationMST approximationClass( verticesCount, graph, MST ); 
        vector<int> appAnswer = approximationClass.findAnswerCycle();
        /*for( int i = 0; i < appAnswer.size(); ++i ) // Вывод нашего пути.
            cout << appAnswer[i] << ' ' << endl;*/
        double answerLen = approximationClass.getAnswerCycleLen();
        cout << "Our length: " << answerLen << endl;
        // Поиск кратчайшего пути.
        CHamiltonianCycleExhaustiveSearch ExhaustSolve( graph, verticesCount );
        ExhaustSolve.findShortestCycle();
        double ExhaustAnswer = ExhaustSolve.getAnswerCycleLen();
        cout << "Best length: " << ExhaustAnswer << endl;
        cout << endl;
        difference[i] = answerLen - ExhaustAnswer;
        sumOfAll += difference[i];
    }
    double average = sumOfAll / experimentsCount;
    cout << "Average deviation: " << average << endl;
    double dispersionSum = 0;
    for( int i = 0; i < experimentsCount; ++i ) {
        dispersionSum += std::abs( difference[i] - average );
    }
    double dispersion = dispersionSum / experimentsCount;
    cout << "Dispersion: " << dispersion << endl;
    cout << "Standart diviation: " << sqrt( dispersion ) << endl;
    cin >> verticesCount;
    return 0;
}