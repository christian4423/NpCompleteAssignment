// NpComplete1.cpp : Defines the entry point for the console application.
/* project.cpp : CSE830 Term Project */
/* Micky Badgero */
/* April 7, 2003 */
#include "stdafx.h"
using namespace std;




int main(int argc, char* argv[])
{
	bool finished = 0;
	double seconds;  /* run time seconds */

	ifstream Graph;  /* input file stream */


	DataObject data = DataObject();
	data.initialize();


	string ftype, fwidth, fheight;
	string inputfPath = "Input/";
	string outfPath = "Output/";
	string fname;
	string fileString;
	if (argc>1)
	{
		cout << "input file name: " << argv[1] << "\n";
		fileString = argv[1];
	}
	else
	{
		cout << "Please enter the type: ";
		cin >> ftype;
		cout << "\n";
		cout << "Please enter the |x| length: ";
		cin >> fwidth;
		cout << "\n";
		cout << "Please enter the |y| length: ";
		cin >> fheight;
		cout << "\n";
		inputfPath += ftype + "/";
		outfPath += ftype + "/";
		fname = ftype + "-" + fwidth + "-" + fheight;
	}
	cout << "Output file path is: " << outfPath << ".txt\n";
	cout << "Output file name is: " << fileString << ".txt\n";
	cout << "Output full path is: " << outfPath << fname << ".txt\n";
	cout << "Old file of this name is overwritten\n";
	fileString = inputfPath + fname;
	clock_t start, stop;
	start = clock();

	Graph.open(fileString.data());
	assert(Graph.is_open());

	Graph >> data.vertices;
	if (data.vertices>100)
	{
		cout << "Maximum vertices in Graph is 100\n";
		return 1;
	}

	Graph >> data.edgeCount; /* this number is necessary to verify edge coverage */
	Graph >> data.node1;
	Graph >> data.node2;

	while (!Graph.eof())
	{
		data.matrix[data.node1][data.node2] = 1;
		data.matrix[data.node2][data.node1] = 1;

		Graph >> data.node1;
		Graph >> data.node2;
	}

	Graph.close();
	cout << "\n input file read \n";

	/* set the matrix columns */
	data.edges = data.vertices + 1;
	data.required = data.vertices + 2;
	data.notRequired = data.vertices + 3;
	data.maybe = data.vertices + 4;
	data.maybeNot = data.vertices + 5;
	data.sort = data.vertices + 6;
	data.test = data.vertices + 7;
	data.best = data.vertices + 8;
	data.verify = data.vertices + 9;

	for (data.i = 0; data.i<data.vertices; data.i++) /* find the number of edges per node */
	{
		for (data.j = 0; data.j<data.vertices; data.j++)
			data.matrix[data.i][data.edges] = data.matrix[data.i][data.edges] + data.matrix[data.i][data.j];
			data.matrix[data.i][data.vertices] = data.i; /* set the node number column */
	}

	/* check for zero or one edges */
	//zeroOne(matrix, vertices, edges, required, notRequired, maybeNot);

	/* check for two edges */
	//twoEdges(matrix, vertices, edges, required, notRequired);

	/* sort nodes descending by number of edges */
	sortNodes(data.matrix, data.vertices, data.edges, data.sort);

	/* check to see if a solution has been found for vertex cover*/
	//solution(matrix, vertices, required, notRequired, maybe, maybeNot, finished);

	/* go thru combinations of unfound nodes to find optimal solution */
	if (!data.finished)
	{
		cout << " some brute force search required\n";


		for (data.i = 1; data.i<data.vertices; data.i++)
		{
			recurse(data.matrix, data.vertices, data.edges, data.required, data.notRequired,
				data.maybe, data.maybeNot, data.sort, data.test, data.best, data.verify, data.finished,
				data.count, data.mask, data.i, data.i - 1, data.edgeCount);
			if (data.finished) break;
		}
	}

	/* calculate and display the run time */
	stop = clock();
	seconds = stop - start;
	seconds = seconds / CLOCKS_PER_SEC;
	data.minutes = (int)(seconds / 60);
	seconds = seconds - (double)(data.minutes * 60);
	fileString = outfPath + fname;
	output(data.matrix, data.vertices, seconds, fileString, data.edgeCount);

	/* output the numbers of the required vertices */
	cout << "\n Required vertices: " << "\n\n";
	data.j = 0;
	for (data.i = 0; data.i<data.vertices; data.i++)
	{
		if (data.matrix[data.i][data.required] == 1)
		{
			cout << "  " << data.matrix[data.i][data.vertices];
			data.j++;
		}
	}

	cout << "\n\n Total number of required vertices: " << data.j << "\n";

	cout << "  Run time: " << data.minutes << ":";
	if (seconds / 10<1) cout << "0";
	cout << seconds << "\n\n";

	return 0;
}

