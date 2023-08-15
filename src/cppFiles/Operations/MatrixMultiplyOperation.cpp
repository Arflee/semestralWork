#include "MatrixMultiplyOperation.h"

bool MatrixMultiplyOperation::HandleErrors(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() < 3)
    {
        cout << "Please write second matrix variable" << endl;
        return true;
    }
    else if (consoleArgs.size() > 4)
    {
        cout << "Too many arguments, the semanitcs are: mmul MATRIX_NAME MATRIX_NAME2 [OUTPUT_NAME]" << endl;
        return true;
    }
    else if (consoleArgs.size() == 3)
    {
        hasOnlyStandardArgument = true;
        return false;
    }

    hasOnlyStandardArgument = false;
    return false;
}

void MatrixMultiplyOperation::HandleOperation(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>& variables)
{
    auto& firstMatrix = variables[consoleArgs[1]];
    auto& secondMatrix = variables[consoleArgs[2]];

    if (firstMatrix == nullptr || secondMatrix == nullptr)
    {
        cout << "ERROR: The given matrices were not found in the variables" << endl;
        return;
    }

    auto output = (*firstMatrix) * (*secondMatrix);

    if (output == nullptr)
    {
        cout << "ERROR: The matrices have wrong sizes" << endl;
        return;
    }

    if (hasOnlyStandardArgument)
    {
        cout << *output;
        return;
    }

    variables[consoleArgs[3]] = output;
}

string MatrixMultiplyOperation::GetName() const
{
    return "mmul";
}

string MatrixMultiplyOperation::GetDescription() const
{
    return "mmul MATRIX_NAME MATRIX_NAME2 [OUTPUT_NAME]\n Multiplies two matrices and returns result to third variable if it was entered";
}
