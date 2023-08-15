#include "PrintOperation.h"

bool PrintOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() < 2)
    {
        cout << "ERROR: Write the name of variable, which you want to print" << endl;
        return true;
    }
    else if (consoleArgs.size() > 2)
    {
        cout << "ERROR: Too many arguments, the semanitcs are: print MATRIX_NAME" << endl;
        return true;
    }
    return false;
}

void PrintOperation::HandleOperation(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>& variables)
{
    auto& matrix = variables[consoleArgs[1]];
    if (matrix == nullptr)
    {
        cout << "ERROR: The given matrix was not found in the variables";
        return;
    }

    cout << *matrix << endl;
}

string PrintOperation::GetName() const
{
    return "print";
}

string PrintOperation::GetDescription() const
{
    return "print MATRIX_NAME\n Prints entered matrix to the console";
}
