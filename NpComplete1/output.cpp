#include "stdafx.h"
/*********************************************************************/
/* output results to file                                            */
/*********************************************************************/
void output(int matrix[maxVertices][maxVertices + 10],
	int vertices, double seconds, string fileString, int edgeCount)
{
	/* write the matrix to the output file */
	int i, j,
		best = vertices + 8,
		edges = vertices + 1,
		maybe = vertices + 4,
		maybeNot = vertices + 5,
		min,
		minutes,
		notRequired = vertices + 3,
		required = vertices + 2,
		sort = vertices + 6,
		test = vertices + 7,
		verify = vertices + 9;

	/* open the output file */
	ofstream Out;
	fileString = fileString + ".txt";
	Out.open(fileString.data());
	Out << "Results for " << fileString << "\n\n";

	/* output column numbers and stats labels */
	Out << "\n";
	for (i = 0; i<vertices; i++)
	{
		if (matrix[i][vertices] / 10>0) Out << " " << matrix[i][vertices];
		else Out << "  " << matrix[i][vertices];
	}
	Out << "   V  E  R\n\n";

	for (i = 0; i<vertices; i++)
	{
		for (j = 0; j<vertices; j++)
		{
			Out << "  " << matrix[i][j];
		}

		if (matrix[i][vertices] / 10>0) Out << "  " << matrix[i][vertices];
		else Out << "   " << matrix[i][vertices];
		if (matrix[i][edges] / 10>0) Out << " " << matrix[i][edges];
		else Out << "  " << matrix[i][edges];
		Out << "  " << matrix[i][required];
		Out << "\n";
	}

	/******* verify solution ********/
	Out << "\n Edge Count: " << edgeCount << "\n";
	for (i = 0; i<vertices; i++)
	{
		if (matrix[i][required] == 1)
		{
			matrix[i][verify] = 1;
			for (j = 0; j<vertices; j++)
			{
				if (matrix[i][j] == 1)
				{
					matrix[j][verify] = 1;
				}
			}
		}
	}
	Out << "\n";
	for (i = 0; i<vertices; i++)
	{
		Out << "  " << matrix[i][verify];
	}

	/* output column numbers and stats labels */
	Out << "\n\n";
	for (i = 0; i<vertices; i++)
	{
		if (matrix[i][vertices] / 10>0) Out << " " << matrix[i][vertices];
		else Out << "  " << matrix[i][vertices];
	}
	Out << "   V  E  R\n";

	/* output the numbers of the required vertices */
	Out << "\n\n Required vertices: " << "\n";
	min = 0;
	for (i = 0; i<vertices; i++)
	{
		if (matrix[i][required] == 1)
		{
			Out << "\n  " << matrix[i][vertices];
			min++;
		}
	}

	Out << "\n\n Total number of required vertices: " << min << "\n\n";

	minutes = (int)(seconds / 60);
	seconds = seconds - (double)(minutes * 60);
	Out << "Run time: " << minutes << ":";
	if (seconds / 10<1) Out << "0";
	Out << seconds << "\n";

	Out.close();
}