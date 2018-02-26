#include "stdafx.h"
/*********************************************************************/
/* recursive program to output combinations of selections of size i  */
/*********************************************************************/
void recurse(int matrix[maxVertices][maxVertices + 10],
	int vertices, int edges,
	int required, int notRequired,
	int maybe, int maybeNot,
	int sort,
	int test, int best,
	int verify, bool &finished,
	int count[], int mask[], int i, int j, int edgeCount)
{
	int n = 0;
	if (finished == 0)
	{
		i--;
		if (i == 0)
		{
			for (count[i] = count[i + 1] + 1; count[i]<vertices - i; count[i]++)
			{
				mask[count[i]] = 1;
				brute(matrix, vertices, edges, required, notRequired,
					maybe, maybeNot, sort, test, best, verify, finished, mask, edgeCount);
				mask[count[i]] = 0;
				if (finished == 1) break;
			}
		}
		else if (i == j)
		{
			for (count[i] = 0; count[i]<vertices - i; count[i]++)
			{
				mask[count[i]] = 1;
				recurse(matrix, vertices, edges, required, notRequired,
					maybe, maybeNot, sort, test, best, verify, finished,
					count, mask, i, j, edgeCount);
				mask[count[i]] = 0;
				if (finished == 1) break;
			}
		}
		else
		{
			for (count[i] = count[i + 1] + 1; count[i]<vertices - i; count[i]++)
			{
				mask[count[i]] = 1;
				recurse(matrix, vertices, edges, required, notRequired,
					maybe, maybeNot, sort, test, best, verify, finished,
					count, mask, i, j, edgeCount);
				mask[count[i]] = 0;
				if (finished == 1) break;
			}
		}
		i++;
	}
}