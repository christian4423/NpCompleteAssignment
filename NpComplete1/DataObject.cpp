#include "stdafx.h"
DataObject::DataObject() {
	initialize();
}
void DataObject::initialize() {
	finished = 0;
	for (i = 0; i<maxVertices; i++) /* initialize the graph adjacency matrix */
	{
		/**
		* Added count & mask in loop. Windows default value were too big.
		* Christian M.
		*/
		count[i] = i;
		mask[i] = i;
		for (j = 0; j<maxVertices + 10; j++)
		{
			matrix[i][j] = 0;
		}
	}
}