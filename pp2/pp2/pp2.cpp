#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

void NinetyFour();
void fiftyOne();
void FiftyFive();
void Ten();
void TenF(double* pMatrix, double* pVector, double* pResult, int Size);
int main()
{
	Ten();
	
}

void fiftyOne()
{
	FILE* fp;
	fopen_s(&fp, "S1.txt", "w");

	double start = omp_get_wtime();
	
	int n = 1000;

#pragma omp parallel for schedule(static) 
	for (int x = 1; x <= n; x++)
	{
		for (int y = 1; y <= n; y++)
		{
			for (int z = 1; z <= n; z++)
			{
				if (x + y + z == n)
				{
					fprintf(fp, "%d %d %d %d\n", x, y, z);
					
				}
			}
		}
	}

	fclose(fp);
	printf("time = %lf\nsum2=%d", omp_get_wtime() - start);
}

void NinetyFour() {
	
	int N = 10000;

	double sum = 0;
	double	start = omp_get_wtime();
#pragma omp parallel for reduction (+:sum)
	for (int  i = 1; i <= N; i++)
		for (int  j = -i; j <= N; j++)
		{		
			sum += (sin(i) * cos(j)) / (4 + (i * i) + (j * j * j * j));
		}
	printf("Sum =", sum);
	printf("Time =", omp_get_wtime() - start);
		
}

void FiftyFive() {
	int n = 2147483647;
	double ln2 = 0;
	double test;
	double start = omp_get_wtime();

#pragma omp parallel for reduction (+:ln2)
		for (int i = 1; i < n; i++)
		{		
			ln2 += (double)((i % 2 == 0) ? -1 : 1) / i;
		}

		printf("time = %lf\nln2=%.40lf", omp_get_wtime() - start, ln2);
}

void Ten() {

	const int n = 1;
	double mass[n * n]{ 0 };
	double vec[n]{ 0 };
	double Result[n]{ 0 };
	for (int i = 0; i < (n*n); i++)
	{	
		mass[i] = rand() % 10;		
	}
	for (int i = 0; i < n; i++)
	{
		vec[i] = rand() % 10;
	}
	 TenF(mass, vec, Result, n);
	 cout << Result[0];
}

void TenF(double* pMatrix, double* pVector,double* pResult, int Size) {
		int i, j;
#pragma omp parallel for private (j)
	for (i = 0; i < Size; i++) {
		for (j = 0; j < Size; j++) {
			pResult[i] += pMatrix[i * Size + j] * pVector[j];
		}
	}
}

