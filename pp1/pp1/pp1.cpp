#include <iostream>
#include <omp.h>
#include <thread>
using namespace std;

void test() {
	int n = 2147483647;
	double ln2 = 0;
	double test;
	double start = omp_get_wtime();

#pragma omp parallel
	{
		#pragma omp for private (test), reduction (+:ln2)
		for (int i = 1; i < n; i++)
		{
			test = 0;
			test += (double)((i % 2 == 0) ? -1 : 1) / i;
			ln2 += test;
		}
	}
	printf("time = %lf\nln2=%.40lf", omp_get_wtime() - start, ln2);
}

int main()
{
	thread thd(test);
	thd.join();
	
}

