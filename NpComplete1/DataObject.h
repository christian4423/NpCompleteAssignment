#pragma once
#ifndef DATA_OBJECT_H					// avoid repeated expansion
#define DATA_OBJECT_H
#include "stdafx.h"
class DataObject {
public:
	int i;                  /* loop counters */
	int j;                  /* loop counters */
	int	best;               /* best combination found so far, column of matrix matrix */
	int	edgeCount;          /* number of edges for each node; column of matrix matrix after file read */
	int edges;              /* number of edges for each node; column of matrix matrix after file read */
	int	matrix[maxVertices][maxVertices + 10]; /* adjacency matrix of graph */
	int	maybe;              /* nodes that may be needed and are being tested; column of matrix matrix */
	int	maybeNot;           /* nodes that may not be needed and are being tested; column of matrix matrix */
	int	minutes;            /* run time minutes */
	int node1;              /* temporary nodes to read input file lines into */
	int node2;              /* temporary nodes to read input file lines into */
	int	notRequired;        /* nodes determined not to be needed; column of matrix matrix */
	int required;           /* nodes determined to be needed; column of matrix matrix */
	int	sort;               /* sort column of matrix matrix */
	int	test;               /* test combination to see if it is a solution and how many nodes are required */
	int	verify;             /* matrix column for verifying solution */
	int	vertices;           /* number of nodes in the graph */
	bool finished;
	int count[maxVertices]; /* count array */
	int mask[maxVertices];  /* mask array */
	DataObject();
	void initialize();
};
#endif