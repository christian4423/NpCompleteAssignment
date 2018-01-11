/* project.cpp : CSE830 Term Project */
/* Micky Badgero */
/* April 7, 2003 */

#include <cassert>
#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

#define maxVertices 101
#define MAX 10

void brute(int matrix[maxVertices][maxVertices+10], int vertices, int edges, 
		   int required, int notRequired, int maybe, int maybeNot, 
		   int sort, int test, int best, int verify, bool &finished, int mask[], int edgeCount);
void sortNodes(int matrix[maxVertices][maxVertices+10], int vertices, int edges, 
			   int sort);
void output(int matrix[maxVertices][maxVertices+10], int vertices, 
			double seconds, string fileString, int edgeCount);
void recurse(int matrix[maxVertices][maxVertices+10], int vertices, int edges,
		     int required, int notRequired, int maybe, int maybeNot,
		     int sort, int test, int best, int verify, bool &finished,
			 int count[], int mask[], int i, int j, int edgeCount);
void solution(int matrix[maxVertices][maxVertices+10], int vertices, 
			  int required, int notRequired, int maybe, int maybeNot,
			  bool &finished, int edgeCount, int test);
void twoEdges(int matrix[maxVertices][maxVertices+10], int vertices, int edges, 
			  int required, int notRequired);
void zeroOne(int matrix[maxVertices][maxVertices+10], int vertices, int edges, 
			 int required, int notRequired, int maybeNot);

int main(int argc, char* argv[])
{
	bool finished = 0;
	double seconds;  /* run time seconds */

	ifstream Graph;  /* input file stream */

	int i,j,         /* loop counters */
		best,        /* best combination found so far, column of matrix matrix */
		edgeCount,       /* number of edges for each node, column of matrix matrix after file read */
		edges,       /* number of edges for each node, column of matrix matrix after file read */
		matrix[maxVertices][maxVertices+10], /* adjacency matrix of graph */
		maybe,       /*nodes that may be needed and are being tested, column of matrix matrix */
		maybeNot,    /*nodes that may not be needed and are being tested, column of matrix matrix */
		minutes,     /* run time minutes */
		node1,node2, /* temporary nodes to read input file lines into */
		notRequired, /* nodes determined not to be needed, column of matrix matrix */
		required,    /* nodes determined to be needed, column of matrix matrix */
		sort,        /* sort column of matrix matrix */
		test,        /* test combination to see if it is a solution and how many nodes are required */
		verify,      /* matrix column for verifying solution */
		vertices;    /* number of nodes in the graph */
	int count[maxVertices]; /* count array */
	int mask[maxVertices];  /* mask array */

	for(i=0; i<maxVertices; i++) /* initialize the graph adjacency matrix */
	{
		for(j=0; j<maxVertices+10; j++)
		{
			matrix[i][j]=0;
	}	}

	string fileString;
	if(argc>1)
	{
		cout << "input file name: " << argv[1] << "\n";
		fileString=argv[1];
	}
	else
	{
		cout << "Please enter the input file name: ";
		cin >> fileString;
		cout << "\n";
	}
	cout << "Output file name is: " << fileString << ".txt\n";
	cout << "Old file of this name is overwritten\n";

	clock_t start,stop;
	start=clock();

	Graph.open(fileString.data());
	assert(Graph.is_open());

	Graph >> vertices;
	if(vertices>100) 
	{
		cout << "Maximum vertices in Graph is 100\n";
		return 1;
	}

	Graph >> edgeCount; /* this number is necessary to verify edge coverage */
	Graph >> node1;
	Graph >> node2;

	while(!Graph.eof())
	{
		matrix[node1][node2]=1;
		matrix[node2][node1]=1;

		Graph >> node1;
		Graph >> node2;
	}

	Graph.close();
	cout <<"\n input file read \n";

	/* set the matrix columns */
	edges = vertices + 1;
	required = vertices + 2;
	notRequired = vertices + 3;
	maybe = vertices + 4;
	maybeNot = vertices + 5;
	sort = vertices + 6;
	test = vertices + 7;
	best = vertices + 8;
	verify = vertices + 9;

	for(i=0; i<vertices; i++) /* find the number of edges per node */
	{
		for(j=0; j<vertices; j++)
			matrix[i][edges] = matrix[i][edges] + matrix[i][j];
		matrix[i][vertices] = i; /* set the node number column */
	}

	/* check for zero or one edges */
	//zeroOne(matrix, vertices, edges, required, notRequired, maybeNot);

	/* check for two edges */
	//twoEdges(matrix, vertices, edges, required, notRequired);

	/* sort nodes descending by number of edges */
	sortNodes(matrix, vertices, edges, sort);

	/* check to see if a solution has been found for vertex cover*/
	//solution(matrix, vertices, required, notRequired, maybe, maybeNot, finished);

	/* go thru combinations of unfound nodes to find optimal solution */
	if(!finished)
	{
		cout << " some brute force search required\n";
		

		for(i=1; i<vertices; i++)
		{
			recurse(matrix, vertices, edges, required, notRequired, 
				maybe, maybeNot, sort, test, best, verify, finished, 
				count, mask, i, i-1, edgeCount);
			if(finished) break;
	}	}

	/* calculate and display the run time */
	stop=clock();
	seconds=stop-start;
	seconds=seconds/CLOCKS_PER_SEC;
	minutes=(int)(seconds/60);
	seconds=seconds-(double)(minutes*60);

	output(matrix, vertices, seconds, fileString, edgeCount);

	/* output the numbers of the required vertices */
	cout << "\n Required vertices: " << "\n\n";
	j=0;
	for (i=0;i<vertices; i++)
	{
		if(matrix[i][required]==1) 
		{
			cout << "  " << matrix[i][vertices];
			j++;
	}	}

	cout << "\n\n Total number of required vertices: " << j << "\n";

	cout << "  Run time: " << minutes << ":";
	if(seconds/10<1) cout << "0";
	cout << seconds << "\n\n";

	return 0;
}

/*********************************************************************/
/* Brute force algorithm to find optimal solution.                   */
/*********************************************************************/
void brute(int matrix[maxVertices][maxVertices+10], 
		   int vertices, int edges,
		   int required, int notRequired,
		   int maybe, int maybeNot,
		   int sort,
		   int test, int best,
		   int verify, bool &finished, int mask[], int edgeCount)
{
	int i,j,k; /* loop counters */

	/* use mask to find necessary test positions */
	for(i=0; i<vertices; i++)
	{
		/* reset the maybe and maybeNot fields for another test */
		matrix[i][maybe]=0;
		matrix[i][maybeNot]=0;
		matrix[i][test]=0;
	}

	j=0;
	for(i=0; i<vertices; i++)
	{
		if(matrix[i][required]==0 && matrix[i][notRequired]==0)
		{
			matrix[i][test]=mask[j];
			j++; /* number of test vertices */
		}
		else 
			matrix[i][test]=0;
	}

	/* set binary value into maybe field of matrix */
	/* and find all the nodes that have connections to these required vertices */
/*
	for(i=0; i<vertices; i++)
	{
		if(matrix[i][test]==1 || matrix[i][required]==1) 
		{
			matrix[i][maybe]=1;
			for(j=0; j<vertices; j++)
			{
				if(matrix[i][j]==1)
					matrix[j][maybeNot]=1;
	}	}	}
*/
	/* test for finished, see if all vertices are covered */
	solution(matrix, vertices, required, notRequired, maybe, maybeNot, finished, edgeCount, test);

	if(finished==1 )
	{
		j=0;
		for(i=0; i<vertices; i++)
		{
			if(matrix[i][test]==1)
				j++;
		}
		k=0;
		for(i=0; i<vertices; i++)
		{
			if(matrix[i][test]==1)
				matrix[i][required]=1;
}	}	}

/*********************************************************************/
/* output results to file                                            */
/*********************************************************************/
void output(int matrix[maxVertices][maxVertices+10], 
			int vertices, double seconds, string fileString, int edgeCount)
{
	/* write the matrix to the output file */
	int i,j,
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
	fileString = fileString +".txt";
	Out.open(fileString.data());
	Out << "Results for " << fileString << "\n\n";

	/* output column numbers and stats labels */
	Out << "\n";
	for(i=0; i<vertices; i++) 
	{
		if(matrix[i][vertices]/10>0) Out << " " << matrix[i][vertices];
		else Out << "  " << matrix[i][vertices];
	}
	Out << "   V  E  R\n\n";

	for(i=0; i<vertices; i++) 
	{
		for(j=0; j<vertices; j++)
		{
			Out << "  " << matrix[i][j];
		}

		if(matrix[i][vertices]/10>0) Out << "  " << matrix[i][vertices];
		else Out << "   " << matrix[i][vertices];
		if(matrix[i][edges]/10>0) Out << " " << matrix[i][edges];
		else Out << "  " << matrix[i][edges];
		Out << "  " << matrix[i][required];
		Out << "\n";
	}

	/******* verify solution ********/
	Out << "\n Edge Count: " << edgeCount << "\n";
	for(i=0; i<vertices; i++)
	{
		if(matrix[i][required]==1)
		{
			matrix[i][verify]=1;
			for(j=0; j<vertices; j++)
			{
				if(matrix[i][j]==1)
				{
					matrix[j][verify]=1;
	}	}	}	}
	Out << "\n";
	for(i=0; i<vertices; i++)
	{
		Out << "  " << matrix[i][verify];
	}

	/* output column numbers and stats labels */
	Out << "\n\n";
	for(i=0; i<vertices; i++) 
	{
		if(matrix[i][vertices]/10>0) Out << " " << matrix[i][vertices];
		else Out << "  " << matrix[i][vertices];
	}
	Out << "   V  E  R\n";

	/* output the numbers of the required vertices */
	Out << "\n\n Required vertices: " << "\n";
	min=0;
	for (i=0;i<vertices; i++)
	{
		if(matrix[i][required]==1) 
		{
			Out << "\n  " << matrix[i][vertices];
			min++;
	}	}

	Out << "\n\n Total number of required vertices: " << min << "\n\n";

	minutes=(int)(seconds/60);
	seconds=seconds-(double)(minutes*60);
	Out << "Run time: " << minutes << ":";
	if(seconds/10<1) Out << "0";
	Out << seconds << "\n";

	Out.close();
}

/*********************************************************************/
/* recursive program to output combinations of selections of size i  */
/*********************************************************************/
void recurse(int matrix[maxVertices][maxVertices+10], 
		     int vertices, int edges,
		     int required, int notRequired,
		     int maybe, int maybeNot,
		     int sort,
		     int test, int best,
		     int verify, bool &finished,
			 int count[], int mask[], int i, int j, int edgeCount)
{
	int n=0;
	if(finished==0)
	{
		i--;
		if(i==0)
		{
			for(count[i]=count[i+1]+1; count[i]<vertices-i; count[i]++)
			{
				mask[count[i]]=1;
				brute(matrix, vertices, edges, required, notRequired, 
					maybe, maybeNot, sort, test, best, verify, finished, mask, edgeCount);
				mask[count[i]]=0;
				if(finished==1) break;
		}	}
		else if(i==j)
		{
			for(count[i]=0; count[i]<vertices-i; count[i]++)
			{
				mask[count[i]]=1;
				recurse(matrix, vertices, edges, required, notRequired, 
					maybe, maybeNot, sort, test, best, verify, finished, 
					count, mask, i, j, edgeCount);
				mask[count[i]]=0;
				if(finished==1) break;
		}	}
		else 
		{
			for(count[i]=count[i+1]+1; count[i]<vertices-i; count[i]++)
			{
				mask[count[i]]=1;
				recurse(matrix, vertices, edges, required, notRequired, 
					maybe, maybeNot, sort, test, best, verify, finished, 
					count, mask, i, j, edgeCount);
				mask[count[i]]=0;
				if(finished==1) break;
		}	}	
		i++;
}	}

/*********************************************************************/
/* check for a possible solution                                     */
/*********************************************************************/
void solution(int matrix[maxVertices][maxVertices+10], int vertices, 
			  int required, int notRequired, int maybe, int maybeNot,
			  bool &finished, int edgeCount, int test)
{
	int i,j,k=0;
	finished=0;
	for(i=0; i<vertices; i++) /* check to see if finished */
	{
		for(j=i; j<vertices; j++) /* count only upper triangle of the matrix */
		{
			if(matrix[i][test]==1 && matrix[i][j]==1 )
				k++;
		}
	}
	if(k==edgeCount)
		finished=1;
}

/*****************************************************************/
/* Node ordering.  Sort the vertices by the number of edges.     */
/*****************************************************************/
void sortNodes(int matrix[maxVertices][maxVertices+10], int vertices, int edges, int sort)
{
	int i,j,k;
	for(i=0; i<vertices-1; i++)
	{
		for(j=i+1; j<vertices; j++)
		{
			if(matrix[i][edges]<matrix[j][edges])
			{
				for(k=0; k<vertices+10; k++)
				{
					/* swap rows */
					/* move i row to sort column of matrix matrix */
					matrix[vertices][k] = matrix[i][k];
					matrix[i][k] = matrix[j][k];
					matrix[j][k] = matrix[vertices][k];
				}
					
				for(k=0; k<vertices; k++)
				{
					/* swap columns */
					/* move i column to sort column of matrix matrix */
					matrix[k][sort] = matrix[k][i];
					matrix[k][i] = matrix[k][j];
					matrix[k][j] = matrix[k][sort];
}	}	}	}	}

/*********************************************************************/
/* if all vertices have two edges, use polynomial optimizer          */
/*********************************************************************/
void twoEdges(int matrix[maxVertices][maxVertices+10], int vertices,
			  int edges, int required, int notRequired)
{
	int i,j,k=0,n; /* loop counters */
	j=0;
	for(i=0; i<vertices; i++)
	{
		if(matrix[i][edges]!=2)
			j=1;
	}
	
	k=0;
	if(j==0)
	{
		for(i=0; i<vertices; i++)
		{
			n=i;
			while(matrix[n][required]==0 && matrix[n][notRequired]==0)
			{
				/* depth first search of undiscovered vertices */
				matrix[n][required]=1;

				j=0; /* find next connecting node */
				while(matrix[n][j]==0 || j==n || j==k) j++; 
				matrix[j][notRequired]=1;

				k=0; /* find next connecting node */
				while(matrix[j][k]==0 || k==j || k==n) k++; 
				matrix[k][notRequired]=1;

				n=0; /* find next n */
				while(matrix[k][n]==0 || n==j || n==k) n++;
}	}	}	}

/*********************************************************************/
/* find node with out degree of zero and set to required             */
/* find vertices with out degree of one,                             */
/*  and set node opposite the edge to required                       */
/*********************************************************************/
void zeroOne(int matrix[maxVertices][maxVertices+10], int vertices,
			 int edges, int required, int notRequired, int maybeNot)
{
	int i,j,k; /* loop counters */

	for(i=0; i<vertices; i++)
	{
		if(matrix[i][edges]==0)
			matrix[i][required]=1;

		if(matrix[i][edges]==1 && matrix[i][required]==0)
		{
			matrix[i][notRequired]=1;
			for(j=0; j<vertices; j++)
			{
				if(matrix[i][j]==1)
				{
					matrix[j][required]=1;
					for(k=0; k<vertices; k++)
					{
						if(matrix[j][k]==1)
							matrix[k][maybeNot]=1;
}	}	}	}	}	}
