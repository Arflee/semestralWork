#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.h"
#include "MatrixType.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"

/**
 * @brief Class used in FileLoadOperation to construct matrix from string input
*/
class MatrixLoader
{
private:
    MatrixType DefineMatrix(const string& type) const;

public:
	shared_ptr<Matrix> CreateMatrix(stringstream& ss, string& outputKey) const;
};
