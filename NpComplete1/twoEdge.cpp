#include "stdafx.h"
/*********************************************************************/
/* if all vertices have two edges, use polynomial optimizer          */
/*********************************************************************/
void twoEdges(int matrix[maxVertices][maxVertices + 10], int vertices,
	int edges, int required, int notRequired)
{
	int i, j, k = 0, n; /* loop counters */
	j = 0;
	for (i = 0; i<vertices; i++)
	{
		if (matrix[i][edges] != 2)
			j = 1;
	}

	k = 0;
	if (j == 0)
	{
		for (i = 0; i<vertices; i++)
		{
			n = i;
			while (matrix[n][required] == 0 && matrix[n][notRequired] == 0)
			{
				/* depth first search of undiscovered vertices */
				matrix[n][required] = 1;

				j = 0; /* find next connecting node */
				while (matrix[n][j] == 0 || j == n || j == k) j++;
				matrix[j][notRequired] = 1;

				k = 0; /* find next connecting node */
				while (matrix[j][k] == 0 || k == j || k == n) k++;
				matrix[k][notRequired] = 1;

				n = 0; /* find next n */
				while (matrix[k][n] == 0 || n == j || n == k) n++;
			}
		}
	}
}