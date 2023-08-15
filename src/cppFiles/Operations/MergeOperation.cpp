#include "MergeOperation.h"
#include "DenseMatrix.h"
#include <algorithm>

void MergeOperation::ToLower(string& str) const
{
    transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c) { return tolower(c); });
}

bool MergeOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() < 3)
    {
        cout << "ERROR: Something is missing in the arguments, please, try one more time" << endl;
        return true;
    }
    else if (consoleArgs.size() > 4)
    {
        cout << "ERROR: Too many arguments, the semanitcs are: add MATRIX_NAME MATRIX_NAME2 [OUTPUT_NAME]" << endl;
        return true;
    }
    else if (consoleArgs.size() == 3)
    {
        string directionString = consoleArgs[3];
        ToLower(directionString);
        MergeDirection direction = Matrix::StringToDirection(directionString);
        hasDirection = direction != MergeDirection::None;
        hasOnlyStandardArgument = !hasDirection;

        return false;
    }


    hasDirection = true;
    hasOnlyStandardArgument = false;
    return false;
}

void MergeOperation::HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables)
{
    auto& firstMatrix = variables[consoleArgs[1]];
    auto& secondMatrix = variables[consoleArgs[2]];

    if (firstMatrix == nullptr || secondMatrix == nullptr)
    {
        std::cout << "ERROR: The given matrices were not found in the variables" << endl;
        return;
    }

    string directionString = consoleArgs[3];
    ToLower(directionString);
    MergeDirection direction = Matrix::StringToDirection(directionString);

    auto output = firstMatrix->Merge(*secondMatrix, direction);
    if (hasOnlyStandardArgument)
    {
        std::cout << *output;
        return;
    }

    variables[consoleArgs[4]] = output;
}

string MergeOperation::GetName() const
{
    return "merge";
}

string MergeOperation::GetDescription() const
{
    return "merge MATRIX_NAME MATRIX_NAME2 [RIGHT or BOTTOM] [OUTPUT_NAME]\n Merges two matices together with given direction";
}
