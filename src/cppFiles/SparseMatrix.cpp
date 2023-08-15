#include <memory>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(int rows, int cols)
{
    this->rows = rows;
    this->columns = cols;
    zerosAmount = rows * columns;
}

SparseMatrix::SparseMatrix(const Matrix& other)
{
    rows = other.GetRowsAmount();
    columns = other.GetColumnsAmount();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (other.Get(i, j) != 0)
            {
                pair<int, int> indexes(i, j);
                matrixValues.insert(make_pair(indexes, other.Get(i, j)));
            }
        }
    }
}

void SparseMatrix::Print(ostream& os) const
{
    int max_len = 0;
    for (auto iter = matrixValues.begin(); iter != matrixValues.end(); ++iter)
    {
        int length = DigitsAmount(iter->second);
        if (length > max_len)
        {
            max_len = length;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            pair<int, int> indexes(i, j);
            auto findIt = matrixValues.find(indexes);
            cout << (j == 0 ? "| " : "") << setw(max_len);
            
            if (findIt != matrixValues.end())
            {
                cout << findIt->second;
            }
            else
            {
                cout << 0;
            }

            cout << (j == columns - 1 ? " |" : " ");
        }

        cout << endl;
    }
}

shared_ptr<Matrix> SparseMatrix::Transpose() const
{
    SparseMatrix output(columns, rows);

    for (auto iter = matrixValues.begin(); iter != matrixValues.end(); ++iter)
    {
        auto indexes = iter->first;
        output.Set(indexes.second, indexes.first, iter->second);
    }

    return make_shared<SparseMatrix>(output);
}

vector<vector<double>> SparseMatrix::GetData() const
{
    vector<vector<double>> output;

    for (int i = 0; i < rows; i++)
    {
        output[i].resize(columns);
        for (int j = 0; j < columns; j++)
        {
            pair<int, int> indexes(i, j);
            auto findIt = matrixValues.find(indexes);

            if (findIt != matrixValues.end())
            {
                output[i].push_back(findIt->second);
            }
            else
            {
                output[i].push_back(0);
            }
        }
    }

    return output;
}

Matrix& SparseMatrix::operator=(const SparseMatrix& other)
{
    if (this == &other) return *this;

    rows = other.GetRowsAmount();
    columns = other.GetColumnsAmount();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (other.Get(i, j) != 0)
            {
                matrixValues.insert(make_pair(make_pair(i, j), other.Get(i, j)));
            }
        }
    }

    return *this;
}

double SparseMatrix::Get(int row, int column) const
{
    pair<int, int> indexes(row, column);
    auto findIt = matrixValues.find(indexes);

    if (findIt != matrixValues.end())
    {
        return findIt->second;
    }

    return 0;
}

void SparseMatrix::Set(int row, int column, double value)
{
    double storedValue = this->Get(row, column);
    pair<int, int> indexes(row, column);

    if (storedValue == 0 && value != 0)
    {
        zerosAmount--;
        matrixValues.insert(make_pair(indexes, value));
    }
    else if (storedValue != 0 && value == 0)
    {
        zerosAmount++;
        matrixValues.erase(indexes);
    }
    else if (storedValue != 0 && value != 0)
    {
        matrixValues[indexes] = value;
    }
}

void SparseMatrix::SaveToFile(ofstream& saveStream, const string& variableKey) const
{
    saveStream << "sparse" << " ";
    saveStream << variableKey << " ";
    saveStream << rows << " " << columns << " ";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            pair<int, int> indexes(i, j);
            auto it = matrixValues.find(indexes);
            auto temp = it;

            if (it  != matrixValues.end())
            {
                saveStream << i << " " << j << " " << it->second;
                if (++temp != matrixValues.end())
                {
                    saveStream << " ";
                }
            }
        }
    }
}
