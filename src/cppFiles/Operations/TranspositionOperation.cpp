#include "TranspositionOperation.h"

bool TranspositionOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() < 2)
    {
        cout << "ERROR: Something is missing in the arguments, please, try one more time" << endl;
        return true;
    }
    else if (consoleArgs.size() > 3)
    {
        cout << "ERROR: Too many arguments, the semanitcs are: tran MATRIX_NAME [OUTPUT_NAME]" << endl;
        return true;
    }
    else if (consoleArgs.size() == 2)
    {
        hasOnlyStandardArgument = true;
        return false;
    }

    hasOnlyStandardArgument = false;
    return false;
}

void TranspositionOperation::HandleOperation(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>& variables)
{
    auto& matrix = variables[consoleArgs[1]];
    if (matrix == nullptr)
    {
        cout << "ERROR: The given matrix was not found in the variables" << endl;
        return;
    }

    auto output = matrix->Transpose();

    if (hasOnlyStandardArgument)
    {
        cout << *output << endl;
        return;
    }

    variables[consoleArgs[2]] = output;
}

string TranspositionOperation::GetName() const
{
    return "tran";
}

string TranspositionOperation::GetDescription() const
{
    return "tran MATRIX_NAME [OUTPUT_NAME]\n Returns a transpose of a matrix";
}
