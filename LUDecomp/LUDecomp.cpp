#include <stdio.h>

void main()
{
	float a[10][10] = { 0 }, l[10][10] = { 0 }, u[10][10] = { 0 }, z[10] = { 0 }, x[10] = { 0 }, b[10] = { 0 };
	int i = 0, j = 0, k = 0, n = 0;
	printf("\nEnter the size of the coeficient matrix ");
	scanf("%d", &n);
	printf("Enter the elements rowwise \n");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			scanf("%f", &a[i][j]);
		}
	}

	printf("Enter the right hand vector\n");

	for (i = 0; i < n; i++)
	{
		scanf("%f", &b[i]);
	}

	// computations of L and U matrices
	for (i = 0; i < n; i++)
	{
		l[i][1] = a[i][1];
	}

	for (j = 1; j < n; j++)
	{
		u[1][j] = a[1][j] / l[1][1];
	}

	for (i = 0; i < n; i++)
	{
		u[i][i] = 1;
	}

	for (i = 1; i < n; i++)
	{
		for (j = 1; j < n; j++)
		{
			if (i >= j)
			{
				l[i][j] = a[i][j];
				for (k = 0; k <= j - 1; k++)
				{
					l[i][k] -= l[i][k] * u[k][j];
				}
			}
			else
			{
				u[i][j] = a[i][j];
				for (k = 0; k <= i - 1; k++)
				{
					u[i][j] -= l[i][k] * u[k][j];
					u[i][j] /= l[i][i];
				}
			}
		}
	}

	printf("\nThe lower triangular matrix L\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < i; j++)
		{
			printf("%f ", l[i][j]);
		}
		printf("\n");
	}

	printf("\nThe upper triangular matrix U\n");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < i; j++)
		{
			printf("             " );
		}

		for (j = i; j < n; j++)
		{
			printf("%.2f ", u[i][j]);
		}
		
		printf("\n");
	}

	// solve lz=b by forward substitution
	z[1] = b[1] / l[1][1];
	for (i = 0; i < n; i++)
	{
		z[i] = b[i];
		for (j = 0; j < i - 1; j++)
		{
			z[i] -= l[i][j] * z[j];
			z[i] /= l[i][i];
		}
	}

	//solve Ux=z by backward substitution 
	x[n] = z[n];
	for (i = n - 1; i > 0; i--)
	{
		x[i] = z[i];
		for (j = i + 1; j <= n; j++)
		{
			x[i] -= u[i][j] * x[j];
		}
	}

	printf("The solution is ");
	for (i = 0; i < n; i++)
	{
		printf("%.2f ", x[i]);
	}
}