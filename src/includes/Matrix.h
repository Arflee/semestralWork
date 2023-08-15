#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include "MergeDirection.h"

using namespace std;

/**
 * @brief Abstract class which implements most part of the matrix operations.
 * The class doesn't know how the values are stored, so the inherited classes have to implement
 * values storage and storage dependent abstract methods
 */
class Matrix
{
private:
    void SwapRows(int, int);
    shared_ptr<Matrix> GetCofactor() const;
    shared_ptr<Matrix> ChooseMatrix() const;

protected:
    double determinant = 1;
    int rows = 2;
    int columns = 2;
    int zerosAmount = 0;

    
    int DigitsAmount(double n) const
    {
        ostringstream strs;
        strs << n;
        return (int)strs.str().size();
    }

public:
    static MergeDirection StringToDirection(string& directionString);

    Matrix() = default;
    virtual ~Matrix() = default;

    int GetRowsAmount() const { return rows; }
    int GetColumnsAmount() const { return columns; }
    int GetZerosAmount() const { return zerosAmount; }

    int Rank() const;
    double Determinant() const;
    shared_ptr<Matrix> Inverse() const;
    shared_ptr<Matrix> GaussMethod() const;
    shared_ptr<Matrix> Merge(const Matrix& other, MergeDirection direction) const;
    shared_ptr<Matrix> Cut(const pair<int, int>& leftCorner, const pair<int, int>& rightCorner) const;

    virtual void Print(ostream& os) const = 0;
    virtual shared_ptr<Matrix> Transpose() const = 0;
    virtual vector<vector<double>> GetData() const = 0;
    virtual void SaveToFile(ofstream& saveStream, const string& variableKey) const = 0;

    shared_ptr<Matrix> operator+(const Matrix& other) const;
    shared_ptr<Matrix> operator-(const Matrix& other) const;
    shared_ptr<Matrix> operator*(const double coefficient) const;
    shared_ptr<Matrix> operator*(const Matrix& other) const;

    Matrix& operator=(const Matrix& other) = delete;
    virtual double Get(int row, int column) const = 0;
    virtual void Set(int row, int column, double value) = 0;

    friend ostream& operator<<(ostream& os, const Matrix& m)
    {
        m.Print(os);
        return os;
    }

    friend ostream& operator<<(ostream& os, const unique_ptr<Matrix>& ptr)
    {
        ptr->Print(os);
        return os;
    }
};