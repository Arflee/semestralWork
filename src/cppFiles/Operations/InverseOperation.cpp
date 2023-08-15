#include "InverseOperation.h"

bool InverseOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() < 2)
    {
        cout << "ERROR: Something is missing in the arguments, please, try one more time" << endl;
        return true;
    }
    else if (consoleArgs.size() > 3)
    {
        cout << "ERROR: Too many arguments, the semanitcs are: inv MATRIX_NAME [OUTPUT_NAME]" << endl;
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

void InverseOperation::HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables)
{
    auto& matrix = variables[consoleArgs[1]];

    if (matrix == nullptr)
    {
        cout << "ERROR: The given matrix was not found in the variables" << endl;
        return;
    }
    
    auto inverse = matrix->Inverse();

    if (inverse == nullptr)
    {
        cout << "ERROR: The matrix is not quadratic" << endl;
        return;
    }
    

    if (hasOnlyStandardArgument)
    {
        cout << *inverse << endl;
        return;
    }

    variables[consoleArgs[2]] = inverse;
}

string InverseOperation::GetName() const
{
    return "inv";
}

string InverseOperation::GetDescription() const
{
    return "inv MATRIX_NAME [OUTPUT_NAME]\n Gets inverse matrix";
}
