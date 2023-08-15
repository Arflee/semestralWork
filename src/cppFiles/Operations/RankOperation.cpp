#include "RankOperation.h"

bool RankOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
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

void RankOperation::HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables)
{
    auto& matrix = variables[consoleArgs[1]];
    if (matrix == nullptr)
    {
        cout << "ERROR: The given matrix was not found in the variables" << endl;
        return;
    }

    int rank = matrix->Rank();
    cout << rank << endl;
}

string RankOperation::GetName() const
{
    return "rank";
}

string RankOperation::GetDescription() const
{
    return "rank MATRIX_NAME\n Writes rank of a matrix to the console";
}
