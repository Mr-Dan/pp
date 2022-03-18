#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	FILE* fp;
	 fopen_s(&fp,"S1.txt", "w");

	double start = omp_get_wtime();	
	int sum = 0;
	int n = 1000;
		
	#pragma omp parallel for reduction(+:sum) 
		for (int x = -n; x <= n; x++)
		{
			for (int y = -n; y <= n; y++)
			{
				for (int z = -n; z <= n; z++)
				{
					if (x + y + z == n)
					{
						fprintf(fp, "%d %d %d %d\n", x, y, z);
						sum ++;
					}
				}
			}
		}

	fclose(fp);
	printf("time = %lf\nsum2=%d", omp_get_wtime() - start, sum);
	
}


