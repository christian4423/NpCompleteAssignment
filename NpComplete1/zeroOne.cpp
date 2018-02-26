#include "stdafx.h"
/*********************************************************************/
/* find node with out degree of zero and set to required             */
/* find vertices with out degree of one,                             */
/*  and set node opposite the edge to required                       */
/*********************************************************************/
void zeroOne(int matrix[maxVertices][maxVertices + 10], int vertices,
	int edges, int required, int notRequired, int maybeNot)
{
	int i, j, k; /* loop counters */

	for (i = 0; i<vertices; i++)
	{
		if (matrix[i][edges] == 0)
			matrix[i][required] = 1;

		if (matrix[i][edges] == 1 && matrix[i][required] == 0)
		{
			matrix[i][notRequired] = 1;
			for (j = 0; j<vertices; j++)
			{
				if (matrix[i][j] == 1)
				{
					matrix[j][required] = 1;
					for (k = 0; k<vertices; k++)
					{
						if (matrix[j][k] == 1)
							matrix[k][maybeNot] = 1;
					}
				}
			}
		}
	}
}