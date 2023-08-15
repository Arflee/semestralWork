#include <memory>
#include <iostream> 
#include <math.h>
#include <iomanip>
#include "Matrix.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"

void Matrix::SwapRows(int row1, int row2)
{
    for (int i = 0; i < columns; i++)
    {
        double temp = this->Get(row1, i);
        this->Set(row1, i, this->Get(row2, i));
        this->Set(row2, i, temp);
    }
}

MergeDirection Matrix::StringToDirection(string& directionString)
{
    if (directionString == "bottom")
    {
        return MergeDirection::Bottom;
    }
    else if (directionString == "right")
    {
        return MergeDirection::Right;
    }
    else
    {
        return MergeDirection::None;
    }
}

int Matrix::Rank() const
{
    int rank = columns;
    DenseMatrix output;
    output = *this;

    for (int row = 0; row < rank; row++)
    {
        // Diagonal element is not zero
        if (output.Get(row, row))
        {
            for (int col = 0; col < rows; col++)
            {
                if (col != row)
                {
                    double mult = output.Get(col, row) / output.Get(row, row);

                    for (int i = 0; i < rank; i++)
                    {
                        double temp = output.Get(col, i);
                        temp -= mult * output.Get(row, i);
                        output.Set(col, i, temp);
                    }
                        
                }
            }
        }
        else
        {
            bool reduce = true;

            /* Find the non-zero element in current
                column  */
            for (int i = row + 1; i < rows; i++)
            {
                // Swap the row with non-zero element
                // with this row.
                if (output.Get(i, row))
                {
                    output.SwapRows(row, i);
                    reduce = false;
                    break;
                }
            }
            if (reduce)
            {
                rank--;

                for (int i = 0; i < rows; i++)
                    output.Set(i, row, output.Get(i, rank));
            }

            // Process this row again
            row--;
        }
    }

    return rank;
}

double Matrix::Determinant() const
{
    auto gemMatrix = this->GaussMethod();

    return gemMatrix->determinant;
}

shared_ptr<Matrix> Matrix::GetCofactor() const
{
    DenseMatrix subMatrix(rows - 1, columns - 1);

    DenseMatrix output;
    output = *this;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int p = 0;
            // Create a submatrix by excluding the current row (i) and column (j)
            for (int x = 0; x < rows; x++) {
                if (x == i) {
                    continue;
                }
                int q = 0;

                for (int y = 0; y < columns; y++) {
                    if (y == j) {
                        continue;
                    }

                    // Set the values of the submatrix by excluding the current row and column
                    subMatrix.Set(p, q, this->Get(x, y));
                    q++;
                }
                p++;
            }

            double temp = pow(-1, i + j) * subMatrix.Determinant();
            output.Set(i, j, temp);
        }
    }

    return make_shared<DenseMatrix>(output);
}

shared_ptr<Matrix> Matrix::ChooseMatrix() const
{
    int wholeMatrixArea = columns * rows;
    if (zerosAmount >= round(wholeMatrixArea / 2. + 0.5))
    {
        return make_shared<SparseMatrix>(*this);
    }

    return make_shared<DenseMatrix>(*this);
}


//To find inverse matrix I use the formula A^(-1) = adj(A) / |A|
shared_ptr<Matrix> Matrix::Inverse() const
{
    if (rows != columns) return nullptr;
    
    double det = Determinant();

    DenseMatrix output;
    output = *this;

    auto temp = output.GetCofactor()->Transpose();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            double el = temp->Get(i, j);
            el /= det;
            temp->Set(i, j, el);
        }

    return temp;
}


shared_ptr<Matrix> Matrix::GaussMethod() const
{
    DenseMatrix output;
    output = *this;

    for (int i = 0; i < output.GetRowsAmount(); i++)
    {
        int pivot = i;
        // Find the pivot element (the element with the maximum absolute value) in the current column
        for (int j = i + 1; j < output.GetRowsAmount(); j++)
            if (fabs(output.Get(j, i)) > fabs(output.Get(pivot, i)))
                pivot = j;
        
        if (pivot != i)
        {
            output.SwapRows(i, pivot);
            output.determinant *= -1;
        }

        output.determinant *= output.Get(i, i);

        // Perform row operations to eliminate the elements below the pivot
        for (int j = i + 1; j < output.GetRowsAmount(); j++)
        {
            double ratio = output.Get(j, i) / output.Get(i, i);

            for (int k = i; k < output.GetRowsAmount(); k++)
            {
                double temp = output.Get(j, k);
                temp -= ratio * output.Get(i, k);
                output.Set(j, k, temp);
            }
        }    
    }
    
    if (output.determinant != output.determinant)
    {
        output.determinant = 0;
    }
    

    return make_shared<DenseMatrix>(output);
}


shared_ptr<Matrix> Matrix::Merge(const Matrix& other, MergeDirection direction) const
{
    int computedRows = 0;
    int computedColumns = 0;

    switch (direction)
    {
    case MergeDirection::None:
    case MergeDirection::Right:
        computedRows = rows;
        computedColumns = columns + other.columns;
        break;
    case MergeDirection::Bottom:
        computedRows = rows + other.rows;
        computedColumns = columns;
        break;
    }

    DenseMatrix output(computedRows, computedColumns);

    for (int i = 0, k = -rows; i < computedRows; i++, k++)
    {
        for (int j = 0, l = -columns; j < computedColumns; j++, l++)
        {
            // If the current row or column index exceeds the number of rows or columns in the current matrix,
            // set the value from the corresponding position in the other matrix
            if (i >= rows)
            {
                output.Set(i, j, other.Get(k, j));
                continue;
            }
            if (j >= columns)
            {
                output.Set(i, j, other.Get(i, l));
                continue;
            }

            output.Set(i, j, this->Get(i, j));
        }
    }

    return output.ChooseMatrix();
}

shared_ptr<Matrix> Matrix::Cut(const pair<int, int>& leftCorner, const pair<int, int>& rightCorner) const
{
    DenseMatrix output(rightCorner.first - leftCorner.first + 1, rightCorner.second - leftCorner.second + 1);
    for (int i = 0, k = leftCorner.first; i < output.GetRowsAmount(); i++, k++)
    {
        for (int j = 0,l = leftCorner.second; j < output.GetColumnsAmount(); j++, l++)
        {
            output.Set(i, j, this->Get(k, l));
        }
    }

    return output.ChooseMatrix();
}

shared_ptr<Matrix> Matrix::operator+(const Matrix& other) const
{
    if (other.GetColumnsAmount() != columns || other.GetRowsAmount() != rows)
    {
        return nullptr;
    }
    
    DenseMatrix newMat(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            double temp = other.Get(i, j) + this->Get(i, j);
            newMat.Set(i, j, temp);
        }
    }

    return newMat.ChooseMatrix();
}

shared_ptr<Matrix> Matrix::operator-(const Matrix& other) const
{
    if (other.GetColumnsAmount() != columns || other.GetRowsAmount() != rows)
    {
        return nullptr;
    }
    
    DenseMatrix newMat(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            double temp = this->Get(i, j) - other.Get(i, j);
            newMat.Set(i, j, temp);
        }
    }

    return newMat.ChooseMatrix();
}

shared_ptr<Matrix> Matrix::operator*(const double coefficient) const
{
    DenseMatrix output(rows, columns);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            output.Set(i, j, this->Get(i, j) * coefficient);
        }
    }
    
    return make_shared<DenseMatrix>(output);
}

shared_ptr<Matrix> Matrix::operator*(const Matrix& other) const
{
    if (columns != other.rows)
    {
        return nullptr;
    }
    
    DenseMatrix output (rows, other.columns);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < other.columns; j++)
            for (int k = 0; k < columns; k++)
            {
                double temp = output.Get(i, j) + this->Get(i, k) * other.Get(k, j);
                output.Set(i, j, temp);

            }
     
    return output.ChooseMatrix();
}