#include "DeterminantOperation.h"

bool DeterminantOperation::HandleErrors(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() < 2)
    {
        cout << "ERROR: Something is missing in the arguments, please, try one more time" << endl;
        return true;
    }
    else if (consoleArgs.size() > 2)
    {
        cout << "ERROR: Too many arguments, the semantics are: gem MATRIX_NAME" << endl;
        return true;
    }

    return false;
}

void DeterminantOperation::HandleOperation(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>& variables)
{
    auto& matrix = variables[consoleArgs[1]];
    if (matrix == nullptr)
    {
        cout << "ERROR: The given matrix was not found in the variables" << endl;
        return;
    }
    else if (matrix->GetColumnsAmount() != matrix->GetRowsAmount())
    {
        cout << "ERROR: Matrix is not quadratic" << endl;
        return;
    }
    
    double determinant = matrix->Determinant();
    cout << determinant << endl;
}

string DeterminantOperation::GetName() const
{
    return "det";
}

string DeterminantOperation::GetDescription() const
{
    return "det MATRIX_NAME\n Writes matrix determinant to the console";
}
