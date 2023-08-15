#pragma once
#include "Matrix.h"

/**
 * @brief Standard matrix class which stores all values presented in a matrix inside two dimensional array
*/
class DenseMatrix : public Matrix
{
protected:
    vector<vector<double>> data;

public:
    DenseMatrix();
    DenseMatrix(int rows, int cols);
    DenseMatrix(const Matrix& other);
    DenseMatrix(initializer_list<vector<double>>);

    void Print(ostream& os) const override;
    shared_ptr<Matrix> Transpose() const override;
    vector<vector<double>> GetData() const override;

    Matrix& operator=(const Matrix& other);
    double Get(int row, int column) const override;
    virtual void Set(int row, int column, double value) override;
    void SaveToFile(ofstream& saveStream, const string& variableKey) const override;
};
