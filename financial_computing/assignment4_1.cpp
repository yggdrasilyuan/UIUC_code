
#include <iostream>
#include <algorithm>
using namespace std;

int a;
float** matrix;

float cal_value(int r, int b)
{
    if (r == 0)
        return (float)b;
    else if (0 == b)
        return 0;
    else if (matrix[r][b] != 0)
        return matrix[r][b];
    else
    {
        float p = ((float)r/(r+b)) * cal_value(r-1, b)+((float)b / (r+b)) * cal_value(r, b-1);
        matrix[r][b] = max((p), (float)(b-r));
        return matrix[r][b];
    }
}

void go(int n)
{
    a = n/2+1;
    matrix = new float*[a];
    for (int i = 0; i<a; i++)
        matrix[i] = new float[a];

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < a; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

int main(int argc,char* argv[])
{
	int num;
	cout << "Please input total number of cards!" << endl;
	// num = atoi(argv[1]);
    cin>>num;
	cout << "Total Number of Cards = " << num << endl;
	go(num);
	float value = cal_value(num/2, num/2);
	cout << "Value of the game = " << value << endl;
    system("pause");
	return 0;

}
