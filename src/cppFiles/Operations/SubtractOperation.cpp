#include "SubtractOperation.h"

bool SubtractOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() < 3)
    {
        cout << "ERROR: Something is missing in the arguments, please, try one more time" << endl;
        return true;
    }
    else if (consoleArgs.size() > 4)
    {
        cout << "ERROR: Too many arguments, the semanitcs are: sub MATRIX_NAME MATRIX_NAME2 [OUTPUT_NAME]" << endl;
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

void SubtractOperation::HandleOperation(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>&variables)
{
    auto& firstMatrix = variables[consoleArgs[1]];
    auto& secondMatrix = variables[consoleArgs[2]];

    if (firstMatrix == nullptr || secondMatrix == nullptr)
    {
        cout << "ERROR: The given matrices were not found in the variables" << endl;
        return;
    }

    auto output = (*firstMatrix) - (*secondMatrix);

    if (output == nullptr)
    {
        cout << "ERROR: Matrices have different sizes" << endl;
        return;
    }

    if (hasOnlyStandardArgument)
    {
        cout << *output;
        return;
    }

    variables[consoleArgs[3]] = output;
}

string SubtractOperation::GetName() const
{
    return "sub";
}

string SubtractOperation::GetDescription() const
{
    return "sub MATRIX_NAME MATRIX_NAME2 [OUTPUT_NAME]\n Subtracts two matrices and returns result to third variable if it was entered";
}
