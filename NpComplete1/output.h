#pragma once
#ifndef OUTPUT_H					// avoid repeated expansion
#define OUTPUT_H
#include "stdafx.h"
using namespace std;
void output(int matrix[maxVertices][maxVertices + 10], int vertices,
	double seconds, string fileString, int edgeCount);
#endif