#include <memory>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "DenseMatrix.h"

DenseMatrix::DenseMatrix()
{
    rows = 2;
    columns = 2;
    zerosAmount = rows * columns;
    this->data = vector<vector<double>>(rows, vector<double>(columns, 0));
}

DenseMatrix::DenseMatrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    zerosAmount = rows * columns;
    this->data = vector<vector<double>>(rows, vector<double>(columns, 0));
}

DenseMatrix::DenseMatrix(const Matrix& other)
{
    rows = other.GetRowsAmount();
    columns = other.GetColumnsAmount();
    data = other.GetData();
}

DenseMatrix::DenseMatrix(initializer_list<vector<double>> arguments)
{
    data.insert(data.end(), arguments.begin(), arguments.end());
    rows = (int)data.size();
    columns = (int)data[0].size();

    if (rows > 1)
        for (int i = 1; i < rows; i++)
            if ((int)data[i].size() != columns)
                throw logic_error("Columns have different sizes");
    
}

void DenseMatrix::Print(ostream& os) const
{
    int max_len = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            const auto num_length = DigitsAmount(data[i][j]);
            if (num_length > max_len)
                max_len = num_length;
        }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            cout << (j == 0 ? "| " : "") << setw(max_len) << data[i][j] << (j == columns - 1 ? " |" : " ");
        
        cout << endl;
    }
}

vector<vector<double>> DenseMatrix::GetData() const
{
    return data;
}


Matrix& DenseMatrix::operator=(const Matrix& other)
{
    if (&other == this) return *this;
    
    rows = other.GetRowsAmount();
    columns = other.GetColumnsAmount();
    data.resize(rows);

    for (int i = 0; i < rows; i++)
    {
        data[i].resize(columns);

        for (int j = 0; j < columns; j++)
            data[i][j] = other.Get(i, j);
    }
    
    return *this;
}

shared_ptr<Matrix> DenseMatrix::Transpose() const
{
    DenseMatrix output(columns, rows);

    for (int i = 0; i < output.rows; i++)
    {
        for (int j = 0; j < output.columns; j++)
        {
            output.Set(i, j, data[j][i]);
        }
    }

    return make_shared<DenseMatrix>(output);
}

double DenseMatrix::Get(int row, int column) const
{
    return data[row][column];
}

void DenseMatrix::Set(int row, int column, double value)
{
    if (data[row][column] == 0 && value != 0) zerosAmount--;
    else if (data[row][column] != 0 && value == 0) zerosAmount++;

    data[row][column] = value;
}

void DenseMatrix::SaveToFile(ofstream& saveStream, const string& variableKey) const
{
    saveStream << "dense" << " ";
    saveStream << variableKey << " ";
    saveStream << rows << " " << columns << " ";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            saveStream << data[i][j];
            if (i < rows - 1 || j < columns - 1)
            {
                saveStream << " ";
            }
        }
    }
}
