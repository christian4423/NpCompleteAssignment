#pragma once
#ifndef BRUTE_H					// avoid repeated expansion
#define BRUTE_H
#include "stdafx.h"
void brute(int matrix[maxVertices][maxVertices + 10], int vertices, int edges,	int required, int notRequired, int maybe, int maybeNot, int sort, int test, int best, int verify, bool &finished, int mask[], int edgeCount);
#endif