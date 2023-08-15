#include "MatrixLoader.h"

MatrixType MatrixLoader::DefineMatrix(const string& type) const
    {
        if (type == "dense") return MatrixType::Dense;
        else if (type == "sparse") return MatrixType::Sparse;
        else return MatrixType::None;
    }

shared_ptr<Matrix> MatrixLoader::CreateMatrix(stringstream& ss, string& outputKey) const
	{
        string matrixType, key;
        int height, width;

        if (!(ss >> matrixType >> key >> height >> width))
        {
            cout << "ERROR: Something went wrong during reading";
            return nullptr;
        }

        outputKey = key;

        MatrixType type = DefineMatrix(matrixType);
        switch (type)
        {
        case MatrixType::None:
        {
            cout << "ERROR: Can't define saved matrix. Please, check saved file on validity";
            return nullptr;
        }
        case MatrixType::Dense:
        {
            DenseMatrix mat(height, width);

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    double element;

                    if (!(ss >> element))
                    {
                        cout << "ERROR: Something went wrong during reading";
                        return nullptr;
                    }
                    mat.Set(i, j, element);
                }
            }
            return make_shared<DenseMatrix>(mat);
        }
        case MatrixType::Sparse:
        {
            SparseMatrix mat(height, width);
            int row;
            int column;
            double value;

            string valuesString;
            while (ss >> row >> column >> value)
            {
                mat.Set(row, column, value);
            }

            return make_shared<SparseMatrix>(mat);
        }
        }

        return nullptr;
	}
