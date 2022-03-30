#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void inputMatrix (double ** A,  int n)
{
	int i, j;

	cout << "Введите вашу матрицу:\n";

	for (i = 1; i <= n; ++i)	
		for (j = 1; j <= n; ++j) 
			cin >> A[i][j];
}

void LUP_Decomposition (double ** A, double ** L, double ** U, int * P, int n) 
{
	int i, j, k, difK;
	double temp, difTemp;

	for (i = 1; i <= n; ++i)
		P[i] = i;
	
	for (k = 1; k <= n; ++k)
	{
		int p = 0;
		for (i = k; i <= n; i++) 
		{
			if (fabs (A[i][k]) > p) 
			{
				p = fabs (A[i][k]);
				difK = i;
			}
		}

		if (p == 0) 
			cout << "Единичная матрица\n";		
		else swap (P[k], P[difK]);
		
		for (i = 1; i <= n; i++)		
			swap (A[k][i], A[difK][i]);
		
		for (i = k + 1; i <= n; ++i)
		{
			temp = A[i][k] / A[k][k];
			A[i][k] = round (temp * 100) / 100;

			for (j = k + 1; j <= n; ++j)
			 {
				temp = A[i][k] * A[k][j];
				difTemp = round (temp * 100) / 100;
				A[i][j] = A[i][j] - difTemp;
			}
		}
	}

	for (i = 1; i <= n; ++i)	
		for (j = 1; j <= n; ++j)		
			if (i == j)
				L[i][j] = 1;			
			else			
				if (i < j)				
					L[i][j] = 0;				
				else L[i][j] = A[i][j];
		
	for (i = 1; i <= n; ++i)	
		for (j = 1; j <= n; ++j)		
			if (i <= j) 
				U[i][j] = A[i][j];			
			else U[i][j] = 0;

	for (i = 1; i <= n; ++i)	
		P[i] -= 1;	
}

void print (int * x, int n) 
{
	int i, j;

	for (i = 1; i <= n; ++i)
		cout << x[i] << "\t";	
}

void printL (double ** L, int n) 
{
	int i, j;
	
	for (i = 1; i <= n; i++) 
	{
		for (j = 1; j <= n; ++j)
			cout << L[i][j] << "\t";
		
		cout << "\n";
	}
}

vector<vector<double>> getMinor (int columnIdx, vector<vector<double>> matrix)
{
    int i, j;
    vector<vector<double>> minor;

    for (i = 1; i < matrix.size(); ++i)
    {
        vector<double> row;

        for (j = 0; j < matrix.size(); ++j)
            if (j != columnIdx)
                row.push_back (matrix[i][j]);

        minor.push_back (row);
    }

    return (minor);
}

int computeDet (vector<vector<double>> matrix)
{
    if (matrix.size() == 1)
        return (matrix[0][0]);

    int det = 0, multiplier = 1, i;

    for (i = 0; i < matrix.size(); ++i)
    {
        int elt = matrix[0][i];

        if (elt != 0)
            det += multiplier * elt * computeDet (getMinor (i, matrix));
        
        multiplier *= -1;
    }

    return (det);
}

void printMatrix (vector<vector<double>> matrix)
{
    int i, j;

    for (i = 0; i < matrix.size(); ++i)
    {
        for (j = 0; j < matrix.size(); ++j)
            cout << matrix[i][j] << " ";

        cout << "\n";
    }
}

void convertArrayToVector (double ** U, vector<vector<double>>& U_vector, int dimension)
{
	int i, j;

	for (i = 1; i <= dimension; ++i)
	{
		vector<double> row;

		for (j = 1; j <= dimension; ++j)
			row.push_back (U[i][j]);

		U_vector.push_back (row);
	}
}

vector<vector<double>> formIdentity (int * P, int dimension)
{
	int i, j;
	vector<vector<double>> permutatedIdentity;

	for (i = 0; i < dimension; ++i)
	{
		vector<double> row (dimension, 0);
		permutatedIdentity.push_back (row);
	}

	for (i = 1; i <= dimension; ++i)
		permutatedIdentity[i - 1][P[i]] = 1;

	return (permutatedIdentity);
}

int main() 
{
	int n, i = 0;
	double ** L = NULL;
	double ** U = NULL;
	int * P = NULL;
	double ** A = NULL;
	
	cout << "Введите размерность матрицы:\n";
	cin >> n;

	L = new double * [n + 1];
	for (i = 1; i <= n; ++i)	
		L[i] = new double[n + 1];
	
	U = new double * [n + 1];
	for (i = 1; i <= n; ++i)
		U[i] = new double[n + 1];
	
	A = new double * [n + 1];
	for (i = 1; i <= n; ++i)
		A[i] = new double[n + 1];

	P = new int[n];

	inputMatrix (A, n);
	LUP_Decomposition (A, L, U, P, n);
	cout << "L:\n";
	printL (L, n);
	cout << "U:\n";
	printL (U, n);
	cout << "P:\n";
	print (P, n);

	vector<vector<double>> U_vector;
	
	cout << "\nОпределитель заданной вами матрицы равен: ";

	convertArrayToVector (U, U_vector, n);
	cout << computeDet (U_vector) * computeDet (formIdentity (P, n)) << "\n";

	return (EXIT_SUCCESS);
}

/*

1 0 0 0 1 0 1 0
0 0 0 0 1 0 1 1
0 1 0 0 0 1 0 0
0 0 0 0 1 1 1 1
0 0 1 0 1 0 0 1
0 0 0 0 0 1 1 0
0 0 0 1 0 1 0 0
0 0 0 0 0 0 1 1

1 0 0 0 1 1 0 0
1 1 0 0 1 0 1 0
0 1 1 0 0 1 0 0
1 0 1 1 1 1 1 1
1 1 0 1 0 0 1 0
0 1 1 0 1 0 0 0
0 0 1 1 0 1 0 0
0 0 0 1 1 0 1 0
*/
