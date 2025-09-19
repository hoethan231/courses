#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void usage()
{
	fprintf(stderr, "Usage: cmd r1 c1 r2 c2\n");
	fprintf(stderr, "arg1: r1, c1 = row, col of matrix 1\n");
}

void fillMatrix(int r, int c, int m[r][c])
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			m[i][j] = (rand() % 10) + 1;
		}
	}
}

void printMatrix(int r, int c, int m[r][c])
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			printf("%d\t", m[i][j]);
		}
		printf("\n");
	}
}

void mulMatrix(int M, int N, int P, int m1[M][N], int m2[N][P], int m3[M][P])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < P; j++)
		{
			m3[i][j] = 0;
			for (int k = 0; k < N; k++)
			{
				m3[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		usage();
		return 1;
	}

	int r1 = atoi(argv[1]);
	int c1 = atoi(argv[2]);
	int r2 = atoi(argv[3]);
	int c2 = atoi(argv[4]);

	if (r1 <= 0 || c1 <= 0 || r2 <= 0 || c2 <= 0)
	{
		fprintf(stderr, "Dimensions must be positive");
		return 1;
	}

	if (c1 != r2)
	{
		fprintf(stderr, "C1: (%d) must match R2 (%d)\n", c1, r2);
		return 1;
	}

	int (*m1)[c1] = malloc((size_t)r1 * sizeof *m1);
	int (*m2)[c2] = malloc((size_t)r2 * sizeof *m2);
	int (*m3)[c2] = malloc((size_t)r1 * sizeof *m3);

	if (!m1 || !m2 || !m3)
	{
		fprintf(stderr, "Out of memory\\n");
		free(m1);
		free(m2);
		free(m3);
	}

	fillMatrix(r1, c1, m1);
	fillMatrix(r2, c2, m2);
	clock_t start_time = clock();
	mulMatrix(r1, c1, c2, m1, m2, m3);
	clock_t end_time = clock();

	double elapsed_seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	if (argc == 6)
	{ // For plotting timing only
		printf("%f", elapsed_seconds);
	}
	else
	{
		printf("Matrix 1:\n");
		printMatrix(r1, c1, m1);
		printf("Matrix 2:\n");
		printMatrix(r2, c2, m2);
		printf("Matrix 1*2:\n");
		printMatrix(r1, c2, m3);
		printf("Execution time: %f seconds\n", elapsed_seconds);
	}

	free(m1);
	free(m2);
	free(m3);

	return 0;
}
