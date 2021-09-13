//#define WITHOUT_NUMPY
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <math.h>
#include <fstream>
#include<string>
#include "Selection.h"
//#include "matplotlib-cpp-master/matplotlibcpp.h"


#define PI 3.14159265

int ARRAYSIZE = 5000000;
int ARRAYMIN = 0;
int ARRAYMAX = 50000000;
int ARRAYINTERVAL = 500000;

using namespace std;

const string functions[] = {"Order", "InvertOrder", "Random", "SawTooth", "Sinusoid", "Step", "QuasiOrdered"};

void OrderInt(int* A, int Size, int Min, int Max);
void InvertOrderInt(int* A, int Size, int Min, int Max);
void RandomInt(int* A, int Size, int Min, int Max);
void SawToothInt(int* A, int Size, int Min, int Max, int Interval);
void SinusoidInt(int* A, int Size, int Min, int Max, int Interval);
void StepInt(int* A, int Size, int Min, int Max, int Interval);
void QuasiOrderedInt(int* A, int Size, int Min, int Max, int Interval);
void Write_in_file(int* A, int Size);


void main()
{
    srand(time(0));

    string Parameters;
    int select = 0;


	while (true)
	{
        int* Array = new int[ARRAYSIZE];

        Parameters = "Parameters:\n ";
        Parameters += "Size: " + to_string(ARRAYSIZE) + "   Min " + to_string(ARRAYMIN) +
            "   Max " + to_string(ARRAYMAX) + "   Interval " + to_string(ARRAYINTERVAL);

        select = Selection(functions, sizeof(functions)/sizeof(string), Parameters);

        switch (select)
        {
        case(0):
            OrderInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX);
            break;

        case(1):
            InvertOrderInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX);
            break;

        case(2):
            RandomInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX);
            break;

        case(3):
            SawToothInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX, ARRAYINTERVAL);
            break;

        case(4):
            SinusoidInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX, ARRAYINTERVAL);
            break;

        case(5):
            StepInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX, ARRAYINTERVAL);
            break;
        case(6):
            QuasiOrderedInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX, ARRAYINTERVAL);
            break;

        default:
            break;
        }
        system("cls");
        cout << "Sequence built" << endl;
        Write_in_file(Array, ARRAYSIZE);
        free(Array);
        system("pause");
	}

    //OrderInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX);

    //InvertOrderInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX);

    //RandomInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX);

    //SawToothInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX, ARRAYINTERVAL);

    //SinusoidInt(Array, ARRAYSIZE, ARRAYMIN, ARRAYMAX, ARRAYINTERVAL);   
}

void Write_in_file(int* A, int Size)
{
    ofstream fout("C:/Tests/GraphData.txt");
    for (int i = 0; i < Size; i++)
    {
        fout << A[i] << " ";
    }
    fout.close();

}

void OrderInt(int* A, int Size, int Min, int Max)
{
    double min = Min;
    double maxstep = double((Max - Min))/double(Size);
    double max = min + maxstep;
    for (int i = 0; i < Size; i++)
    {
        A[i] = int(min + (rand() % int(round((max - min)))));
        min = double(A[i] + 1);
        max += maxstep;
    }

}

void InvertOrderInt(int* A, int Size, int Min, int Max)
{
    double min = Min;
    double maxstep = double(Max - Min) / double(Size);
    double max = min + maxstep;
    for (int i = Size - 1; i >= 0; i--)
    {
        A[i] = int(min + (rand() % int(round((max - min)))));
        min = double(A[i] + 1);
        max += maxstep;
    }

}

void RandomInt(int* A, int Size, int Min, int Max)
{
    int min = Min;
    int max = Max;
    for (int i = 0; i < Size; i++)
    {
        A[i] = min + (rand() % (max - min));
    }
}


void SawToothInt(int* A, int Size, int Min, int Max, int Interval)
{
    int S = 0;
    double maxstep;
    double min;
    double max;
    for (int i = 0; i < Size; i++)
    {
        switch (S)
        {
        case 0:
            min = Min;
            maxstep = double(Max - Min) / double(Interval / 10 * 8);
            max = min + maxstep;
            S = 1;
            break;

        case 1:
            min = double(A[i-1] + 1);
            max += maxstep;
            if (max > Max)
            {
                S = 2;
                i--;
                continue;
            }
            break;
        	
        case 2:
            max = Max;
            maxstep = double(Max - Min) / double(Interval / 10 * 2);
            min = max - maxstep;
            S = 3;
            break;

        case 3:
            max = double(A[i-1] - 1);
            min -= maxstep;
            if (min < Min)
            {
                S = 0;
                i--;
                continue;
            }
            break;

        default:
            break;
        }
        A[i] = int(min + rand() % int(round(max - min)));
    }

}

double SinStepRate(int i, int interval)
{
    return sin(PI * double(double(i % interval) / double(interval / 2))) * 100 / 65;
}

void SinusoidInt(int* A, int Size, int Min, int Max, int Interval)
{
    int S = 0;
    int k = 0.1;
    double min = Min;
    double maxstep = double((Max - Min)) / double(Interval / 2);
    double max = min + maxstep;
    for (int i = 0; i < Size; i++)
    {
        A[i] = int(min + ((double)rand() / (double)RAND_MAX*(max - min)));
        switch (S)
        {
        case 0:
            min = double(A[i] + 1);
            max += maxstep * SinStepRate(i, Interval);
            if (max > Max) S = 1;
            break;

        case 1:
            min -= maxstep * SinStepRate(i, Interval);
            max = double(A[i] - 1);
            if (min < Min) S = 0;

        default:
            break;
        }

    }

}

void StepInt(int* A, int Size, int Min, int Max, int Interval)
{
    double min = Min;
    double maxstep = (Max - Min) / double(Size / Interval);
    double max = min + maxstep;
    for (int i = 0; i < Size; i++)
    {
        A[i] = int(min + ((double)rand() / (double)RAND_MAX * (max - min)));
        if (i % Interval == 0)
        {
            min = max + 1;
            max += maxstep;
        }
    }
}

void QuasiOrderedInt(int* A, int Size, int Min, int Max, int Interval)
{
    int j = 30;
    int* B = new int[Size + j];
    double min = Min;
    double maxstep = double((Max - Min)) / double(Size);
    double max = min + maxstep;
    int tmp = 0;
    for (int i = 0; i < Size+j; i++)
    {
        B[i] = int(min + (rand() % int(round((max - min)))));
        min = double(B[i] + 1);
        max += maxstep;
        if(int((rand() % 100)) < 10) B[i] = int(Min + (rand()*rand() % int(round((Max - Min)))));

        if (i == j)
        {
            for (int ii = j; ii != 0; ii--)
            {
                tmp += B[i - ii];
            }
            A[i - j] = tmp / j;
        }

        if (i > j)
        {
            tmp = tmp + B[i] - B[i - j];
            A[i - j] = tmp / j;
        }
    }
    free(B);
}
