#include "GaussianEliminationOperation.h"

bool GaussianEliminationOperation::HandleErrors(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() > 3)
    {
        cout << "ERROR: Too many arguments, the semantics are: gem MATRIX_NAME [OUTPUT_NAME]" << endl;
        return true;
    }
    if (consoleArgs.size() == 2)
    {
        hasOnlyStandardArgument = true;
        return false;
    }

    hasOnlyStandardArgument = false;
    return false;
}

void GaussianEliminationOperation::HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables)
{
    auto& matrix = variables[consoleArgs[1]];
    if (matrix == nullptr)
    {
        cout << "ERROR: The given matrix was not found in the variables" << endl;
        return;
    }

    auto output = matrix->GaussMethod();

    if (hasOnlyStandardArgument)
    {
        cout << *output;
        return;
    }

    variables[consoleArgs[2]] = output;
}

string GaussianEliminationOperation::GetName() const
{
    return "gem";
}

string GaussianEliminationOperation::GetDescription() const
{
    return "gem MATRIX_NAME [OUTPUT_NAME]\n Return matrix after Gauss-Jordan elimination";
}
