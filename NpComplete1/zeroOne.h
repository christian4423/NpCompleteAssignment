#pragma once
#ifndef ZERO_ONE_H					// avoid repeated expansion
#define ZERO_ONE_H
#include "stdafx.h"
void zeroOne(int matrix[maxVertices][maxVertices + 10], int vertices, int edges,
	int required, int notRequired, int maybeNot);
#endif