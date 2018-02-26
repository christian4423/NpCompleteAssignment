#pragma once
#ifndef RECURSE_H					// avoid repeated expansion
#define RECURSE_H
#include "stdafx.h"
void recurse(int matrix[maxVertices][maxVertices + 10], int vertices, int edges,
	int required, int notRequired, int maybe, int maybeNot,
	int sort, int test, int best, int verify, bool &finished,
	int count[], int mask[], int i, int j, int edgeCount);
#endif