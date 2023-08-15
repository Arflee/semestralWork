#include "CutOperation.h"

bool CutOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() < 6)
    {
        cout << "ERROR: Something is missing in the arguments, please, try one more time" << endl;
        return true;
    }
    else if (consoleArgs.size() > 7)
    {
        cout << "ERROR: Too many arguments, the semanitcs are: cut MATRIX_NAME SCALAR SCALAR SCALAR SCALAR [OUTPUT_NAME]" << endl;
        return true;
    }
    else if (consoleArgs.size() == 6)
    {
        hasOnlyStandardArgument = true;
        return false;
    }

    hasOnlyStandardArgument = false;
    return false;
}

void CutOperation::HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables)
{
    auto& matrix = variables[consoleArgs[1]];
    if (matrix == nullptr)
    {
        cout << "ERROR: The given matrix was not found in the variables" << endl;
        return;
    }
    if (!IsNumber(consoleArgs[2]) || !IsNumber(consoleArgs[3]) ||
        !IsNumber(consoleArgs[4]) || !IsNumber(consoleArgs[5]))
    {
        cout << "ERROR: The coordinates of points must be numbers" << endl;
        return;
    }

    int leftFirst = stoi(consoleArgs[2]);
    int leftSecond = stoi(consoleArgs[3]);
    int rightFirst = stoi(consoleArgs[4]);
    int rightSecond = stoi(consoleArgs[5]);

    if (leftFirst < 1 || leftFirst > matrix->GetRowsAmount() ||
        leftSecond < 1 || leftSecond > matrix->GetColumnsAmount() ||
        rightFirst < 1 || rightFirst > matrix->GetRowsAmount() ||
        rightSecond < 1 || rightSecond > matrix->GetColumnsAmount())
    {
        cout << "ERROR: Points are outside of matrix" << endl;
        return;
    }
    pair<int, int> leftCorner(leftFirst - 1, leftSecond - 1);
    pair<int, int> rightCorner(rightFirst - 1, rightSecond - 1);

    auto output = matrix->Cut(leftCorner, rightCorner);

    if (hasOnlyStandardArgument)
    {
        cout << *output << endl;
        return;
    }

    variables[consoleArgs[6]] = output;
}

string CutOperation::GetName() const
{
    return "cut";
}

string CutOperation::GetDescription() const
{
    return R"(cut MATRIX_NAME SCALAR SCALAR2 SCALAR3 SCALAR4 [OUTPUT_NAME] 
 Cuts matrix on smaller one. The argument uses two points for determening rectangular of slice.
 The first two coordinates correspond to left upper corner. The second two coordinates correspond to right bottom corner)";
}
