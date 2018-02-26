#include "stdafx.h"
/*****************************************************************/
/* Node ordering.  Sort the vertices by the number of edges.     */
/*****************************************************************/
void sortNodes(int matrix[maxVertices][maxVertices + 10], int vertices, int edges, int sort)
{
	int i, j, k;
	for (i = 0; i<vertices - 1; i++)
	{
		for (j = i + 1; j<vertices; j++)
		{
			if (matrix[i][edges]<matrix[j][edges])
			{
				for (k = 0; k<vertices + 10; k++)
				{
					/* swap rows */
					/* move i row to sort column of matrix matrix */
					matrix[vertices][k] = matrix[i][k];
					matrix[i][k] = matrix[j][k];
					matrix[j][k] = matrix[vertices][k];
				}

				for (k = 0; k<vertices; k++)
				{
					/* swap columns */
					/* move i column to sort column of matrix matrix */
					matrix[k][sort] = matrix[k][i];
					matrix[k][i] = matrix[k][j];
					matrix[k][j] = matrix[k][sort];
				}
			}
		}
	}
}