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

int ARRAYSIZE = 50000;
int ARRAYINTERVAL = 5000;

int ARRAYMIN_INT = 0;
int ARRAYMAX_INT = 50000000;


int ARRAYMIN_DOUBLE = 0;
int ARRAYMAX_DOUBLE = 100;



using namespace std;

const string functions[] = {"Order", "InvertOrder", "Random", "SawTooth", "Sinusoid", "Step", "QuasiOrdered\n", "Back"};
const string type[] = { "int", "double"};

void OrderInt(int* A, int Size, int Min, int Max);
void InvertOrderInt(int* A, int Size, int Min, int Max);
void RandomInt(int* A, int Size, int Min, int Max);
void SawToothInt(int* A, int Size, int Min, int Max, int Interval);
void SinusoidInt(int* A, int Size, int Min, int Max, int Interval);
void StepInt(int* A, int Size, int Min, int Max, int Interval);
void QuasiOrderedInt(int* A, int Size, int Min, int Max, int Interval);

void OrderDouble(double* A, int Size, double Min, double Max);
void OrderInvertDouble(double* A, int Size, double Min, double Max);
void RandomDouble(double* A, int Size, double Min, double Max);
void SawToothDouble(double* A, int Size, double Min, double Max, int Interval);
void SinusoidDouble(double* A, int Size, double Min, double Max, int Interval);
void StepDouble(double* A, int Size, double Min, double Max, int Interval);
void QuasiOrderedDouble(double* A, int Size, double Min, double Max);

void Write_in_file(int* A, int Size);
void Write_in_file_double(double* A, int Size);


void main()
{
    srand(time(0));

    string Parameters;
    int select = 0;
    bool back = false;

    while (true)
    {
        back = false;
        select = Selection(type, sizeof(type) / sizeof(string), Parameters);
        switch (select)
        {
        case(0):
            while (!back)
            {
                int* Array = new int[ARRAYSIZE];

                Parameters = "Parameters:\n ";
                Parameters += "Size: " + to_string(ARRAYSIZE) + "   Min " + to_string(ARRAYMIN_INT) +
                    "   Max " + to_string(ARRAYMAX_INT) + "   Interval " + to_string(ARRAYINTERVAL);

                select = Selection(functions, sizeof(functions) / sizeof(string), Parameters);

                switch (select)
                {
                case(0):
                    OrderInt(Array, ARRAYSIZE, ARRAYMIN_INT, ARRAYMAX_INT);
                    break;

                case(1):
                    InvertOrderInt(Array, ARRAYSIZE, ARRAYMIN_INT, ARRAYMAX_INT);
                    break;

                case(2):
                    RandomInt(Array, ARRAYSIZE, ARRAYMIN_INT, ARRAYMAX_INT);
                    break;

                case(3):
                    SawToothInt(Array, ARRAYSIZE, ARRAYMIN_INT, ARRAYMAX_INT, ARRAYINTERVAL);
                    break;

                case(4):
                    SinusoidInt(Array, ARRAYSIZE, ARRAYMIN_INT, ARRAYMAX_INT, ARRAYINTERVAL);
                    break;

                case(5):
                    StepInt(Array, ARRAYSIZE, ARRAYMIN_INT, ARRAYMAX_INT, ARRAYINTERVAL);
                    break;

                case(6):
                    QuasiOrderedInt(Array, ARRAYSIZE, ARRAYMIN_INT, ARRAYMAX_INT, ARRAYINTERVAL);
                    break;

                case(7):
                    back = true;
                    system("cls");
                    continue;

                default:
                    break;
                }
                system("cls");
                cout << "Sequence built" << endl;
                Write_in_file(Array, ARRAYSIZE);
                free(Array);
                system("pause");
            }
            break;

        case(1):
            while (!back)
            {
                double* Array = new double[ARRAYSIZE];

                Parameters = "Parameters:\n ";
                Parameters += "Size: " + to_string(ARRAYSIZE) + "   Min " + to_string(ARRAYMIN_DOUBLE) +
                    "   Max " + to_string(ARRAYMAX_DOUBLE) + "   Interval " + to_string(ARRAYINTERVAL);

                select = Selection(functions, sizeof(functions) / sizeof(string), Parameters);

                switch (select)
                {
                case(0):
                    OrderDouble(Array, ARRAYSIZE, ARRAYMIN_DOUBLE, ARRAYMAX_DOUBLE);
                    break;

                case(1):
                    OrderInvertDouble(Array, ARRAYSIZE, ARRAYMIN_DOUBLE, ARRAYMAX_DOUBLE);
                    break;

                case(2):
                    RandomDouble(Array, ARRAYSIZE, ARRAYMIN_DOUBLE, ARRAYMAX_DOUBLE);
                    break;

                case(3):
                    SawToothDouble(Array, ARRAYSIZE, ARRAYMIN_DOUBLE, ARRAYMAX_DOUBLE, ARRAYINTERVAL);
                    break;

                case(4):
                    SinusoidDouble(Array, ARRAYSIZE, ARRAYMIN_DOUBLE, ARRAYMAX_DOUBLE, ARRAYINTERVAL);
                    break;

                case(5):
                    StepDouble(Array, ARRAYSIZE, ARRAYMIN_DOUBLE, ARRAYMAX_DOUBLE, ARRAYINTERVAL);
                    break;

                case(6):
                    QuasiOrderedDouble(Array, ARRAYSIZE, ARRAYMIN_DOUBLE, ARRAYMAX_DOUBLE);
                    break;

                case(7):
                    back = true;
                    system("cls");
                    continue;

                default:
                    break;
                }
                system("cls");
                cout << "Sequence built" << endl;
                Write_in_file_double(Array, ARRAYSIZE);
                free(Array);
                system("pause");
            }
            break;
        }

    }

	
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

void Write_in_file_double(double* A, int Size)
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



void OrderDouble(double* A, int Size, double Min, double Max)
{
    double min = Min;
    double maxstep = double((Max - Min)) / double(Size);
    double max = min + maxstep;
    for (int i = 0; i < Size; i++)
    {
        A[i] = min + ((double)rand() / (double)RAND_MAX * (max - min));
        min = double(A[i] + maxstep/100);
        max += maxstep;
    }
}

void OrderInvertDouble(double* A, int Size, double Min, double Max)
{
    double min = Min;
    double maxstep = double((Max - Min)) / double(Size);
    double max = min + maxstep;
    for (int i = Size - 1; i >= 0; i--)
    {
        A[i] = min + ((double)rand() / RAND_MAX * (max - min));
        min = double(A[i] + maxstep / 100);
        max += maxstep;
    }
}

void RandomDouble(double* A, int Size, double Min, double Max)
{
    double min = Min;
    double max = Max;
    for (int i = 0; i < Size; i++)
    {
        A[i] = min + ((double)rand() / RAND_MAX * (max - min));
    }
}

void SawToothDouble(double* A, int Size, double Min, double Max, int Interval)
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
            min = double(A[i - 1] + maxstep / 100);
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
            max = double(A[i - 1] - maxstep / 100);
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
        A[i] = min + ((double)rand() / RAND_MAX * (max - min));
    }

}

void SinusoidDouble(double* A, int Size, double Min, double Max, int Interval)
{
    int S = 0;
    double min = Min;
    double maxstep = double((Max - Min)) / double(Interval / 2);
    double max = min + maxstep;
    for (int i = 0; i < Size; i++)
    {
        A[i] = min + ((double)rand() / (double)RAND_MAX * (max - min));
        switch (S)
        {
        case 0:
            min = double(A[i] + maxstep / 100);
            max += maxstep * SinStepRate(i, Interval);
            if (max > Max) S = 1;
            break;

        case 1:
            min -= maxstep * SinStepRate(i, Interval);
            max = double(A[i] - maxstep / 100);
            if (min < Min) S = 0;

        default:
            break;
        }

    }

}

void StepDouble(double* A, int Size, double Min, double Max, int Interval)
{
    double min = Min;
    double maxstep = (Max - Min) / double(Size / Interval);
    double max = min + maxstep;
    for (int i = 0; i < Size; i++)
    {
        A[i] = min + ((double)rand() / (double)RAND_MAX * (max - min));
        if (i % Interval == 0)
        {
            min = max + maxstep / 100;
            max += maxstep;
        }
    }
}

void QuasiOrderedDouble(double* A, int Size, double Min, double Max)
{
    int j = 30;
    double *B = new double[Size + j];
    double min = Min;
    double maxstep = double((Max - Min)) / double(Size);
    double max = min + maxstep;
    double tmp = 0;
    for (int i = 0; i < Size + j; i++)
    {
        B[i] = min + ((double)rand() / (double)RAND_MAX * (max - min));
        min = double(B[i] + maxstep / 100);
        max += maxstep;
        if (int((rand() % 100)) < 10) B[i] = min + ((double)rand()* rand()) / ((double)RAND_MAX * RAND_MAX) * (Max - Min);

        if (i == j)
        {
            for (int ii = j; ii != 0; ii--)
            {
                tmp += B[i - ii];
            }
            A[i - j] = double(tmp / j);
        }

        if (i > j)
        {
            tmp = tmp + B[i] - B[i - j];
            A[i - j] = double(tmp / j);
        }

        if (B[i] > 100)
        {
            int z = 10;
        }
    }
    free(B);
}