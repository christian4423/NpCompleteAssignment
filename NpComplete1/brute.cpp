#include "stdafx.h"
/*********************************************************************/
/* Brute force algorithm to find optimal solution.                   */
/*********************************************************************/
void brute(int matrix[maxVertices][maxVertices + 10],
	int vertices, int edges,
	int required, int notRequired,
	int maybe, int maybeNot,
	int sort,
	int test, int best,
	int verify, bool &finished, int mask[], int edgeCount)
{
	int i, j, k; /* loop counters */

	/* use mask to find necessary test positions */
	for (i = 0; i<vertices; i++)
	{
		/* reset the maybe and maybeNot fields for another test */
		matrix[i][maybe] = 0;
		matrix[i][maybeNot] = 0;
		matrix[i][test] = 0;
	}

	j = 0;
	for (i = 0; i<vertices; i++)
	{
		if (matrix[i][required] == 0 && matrix[i][notRequired] == 0)
		{
			matrix[i][test] = mask[j];
			j++; /* number of test vertices */
		}
		else
			matrix[i][test] = 0;
	}

	/* test for finished, see if all vertices are covered */
	solution(matrix, vertices, required, notRequired, maybe, maybeNot, finished, edgeCount, test);

	if (finished == 1)
	{
		j = 0;
		for (i = 0; i<vertices; i++)
		{
			if (matrix[i][test] == 1)
				j++;
		}
		k = 0;
		for (i = 0; i<vertices; i++)
		{
			if (matrix[i][test] == 1)
				matrix[i][required] = 1;
		}
	}
}