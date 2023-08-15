#include<iostream>
#include<fstream>
#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include "MatrixLoader.h"
#include "FileLoadOperation.h"

bool FileLoadOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() > 1)
    {
        cout << "ERROR: Too many arguments. To load variables from file write \"load\"";
        return true;
    }
    
    return false;
}

void FileLoadOperation::HandleOperation(vector<string>, map<string, shared_ptr<Matrix>>& variables)
{
    ifstream loadFile("save.txt", ios::in);
    if (!loadFile)
    {
        cout << "ERROR: Cannot open file!" << endl;
        return;
    }

    string line;

    while (getline(loadFile, line))
    {
        stringstream ss(line);
        string key;
        MatrixLoader loader;
        auto createdMatrix = loader.CreateMatrix(ss, key);

        if (createdMatrix != nullptr) variables[key] = createdMatrix;
        else break;
    }

    if (loadFile.bad())
    {
        cout << "Error occurred at reading time!" << endl;
        return;
    }
}

string FileLoadOperation::GetName() const
{
    return "load";
}

string FileLoadOperation::GetDescription() const
{
    return "Loads all variables from file";
}
