#pragma once

#include <map>
#include "DenseMatrix.h"

using namespace std;
/**
 * @brief SparseMatrix class where only non-zero values are stored.
 * Class only saves pair of indexes and value in a map.
*/
class SparseMatrix : public Matrix
{
private:
    map<pair<int, int>, double> matrixValues;

public:
    SparseMatrix(int rows, int cols);
    SparseMatrix(const Matrix& other);

    void Print(ostream& os) const override;
    shared_ptr<Matrix> Transpose() const override;
    vector<vector<double>> GetData() const override;
    Matrix& operator=(const SparseMatrix& other);

    double Get(int row, int column) const override;
    void Set(int row, int column, double value) override;

    void SaveToFile(ofstream& saveStream, const string& variableKey) const override;

};
