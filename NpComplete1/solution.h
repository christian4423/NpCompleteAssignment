#pragma once
#ifndef SOLUTION_H					// avoid repeated expansion
#define SOLUTION_H
#include "stdafx.h"
void solution(int matrix[maxVertices][maxVertices + 10], int vertices,
	int required, int notRequired, int maybe, int maybeNot,
	bool &finished, int edgeCount, int test);
#endif