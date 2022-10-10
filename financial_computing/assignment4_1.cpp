
#include <iostream>
#include <algorithm>
using namespace std;

int NUM;//size of array
double** matrix;

double cal_value(int r, int b)
{
    if (r == 0)
        return (double)b;
    else if (0 == b)
        return 0.0;
    else if (matrix[r][b] != 0)
        return matrix[r][b];
    else
    {
        double p = ((double)r/(r+b)) * cal_value(r-1, b)+((double)b / (r+b)) * cal_value(r, b-1);
        matrix[r][b] = max((p), (double)(b-r));
        return matrix[r][b];
    }
}

void play(int n)
{
    NUM = n/2+2;// get more space to put all possibilities
    matrix = new double*[NUM];
    for (int i = 0; i<NUM; i++)
        matrix[i] = new double[NUM];

    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            matrix[i][j] = 0;//init
        }
    }
}

int main(int argc,char* argv[])
{
	int num;
	cout << "Please input total number of cards!" << endl;
    // cin>>num;
    num=atoi(argv[1]);
	cout << "Total Number of Cards = " << num << endl;
	play(num);
	double value = cal_value(num/2, num/2);
	cout << "Value of the game = " << value << endl;
    system("pause");
	return 0;

}
