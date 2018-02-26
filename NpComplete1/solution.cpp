#include "stdafx.h"
/*********************************************************************/
/* check for a possible solution                                     */
/*********************************************************************/
void solution(int matrix[maxVertices][maxVertices + 10], int vertices,
	int required, int notRequired, int maybe, int maybeNot,
	bool &finished, int edgeCount, int test)
{
	int i, j, k = 0;
	finished = 0;
	for (i = 0; i<vertices; i++) /* check to see if finished */
	{
		for (j = i; j<vertices; j++) /* count only upper triangle of the matrix */
		{
			if (matrix[i][test] == 1 && matrix[i][j] == 1)
				k++;
		}
	}
	if (k == edgeCount)
		finished = 1;
}