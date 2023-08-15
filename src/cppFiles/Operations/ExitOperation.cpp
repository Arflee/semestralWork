#include "ExitOperation.h"

bool ExitOperation::HandleErrors(vector<string>,
    map<string, shared_ptr<Matrix>>&)
{
    return false;
}

void ExitOperation::HandleOperation(vector<string>, map<string, shared_ptr<Matrix>>&)
{
    return;
}

string ExitOperation::GetName() const
{
    return GetExitString();
}

string ExitOperation::GetDescription() const
{
    return "Exits the application";
}

string ExitOperation::GetExitString()
{
    return "exit";
}
