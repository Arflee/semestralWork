#include "ComplexOperation.h"
#include <stack>

bool ComplexOperation::HandleErrors(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>&    )
{
    for (size_t i = 0; i < consoleArgs.size(); i++)
    {
        if (consoleArgs[i] == ">")
        {
            if (i == consoleArgs.size() - 2)
            {
                hasOnlyStandardArgument = false;
                return false;
            }
            else
            {
                cout << "ERROR: Something went wrong, please, enter operation one more time";
                return true;
            }
        }
    }

    hasOnlyStandardArgument = true;
    return false;
}

void ComplexOperation::HandleOperation(vector<string> consoleArgs,
    map<string, shared_ptr<Matrix>>& variables)
{
    stack<string> values;
    stack<string> ops;

    for (size_t i = 1; i < consoleArgs.size(); i++)
    {
        if (consoleArgs[i] == ">") break;

        if (consoleArgs[i] == "(")
        {
            ops.push(consoleArgs[i]);
        }
        else if (variables.find(consoleArgs[i]) != variables.end())
        {
            values.push(consoleArgs[i]);
        }
        else if (consoleArgs[i] == ")")
        {
            while (!ops.empty() && ops.top() != "(")
            {
                auto val2 = values.top();
                values.pop();

                auto val1 = values.top();
                values.pop();

                string op = ops.top();
                ops.pop();

                ApplyOperation(val1, val2, op, variables);
                values.push("temp");
            }

            // pop opening brace.
            if (!ops.empty())
                ops.pop();
        }
        else
        {
            while (!ops.empty() && GetOperationPrecedence(ops.top())
                >= GetOperationPrecedence(consoleArgs[i]))
            {
                auto val2 = values.top();
                values.pop();

                auto val1 = values.top();
                values.pop();

                string op = ops.top();
                ops.pop();

                ApplyOperation(val1, val2, op, variables);
                values.push("temp");
            }

            // Push current token to 'ops'.
            if (IsOperation(consoleArgs[i]))
            {
                ops.push(consoleArgs[i]);
            }
            else
            {
                cout << "ERROR: Can't find entered operation or variable" << endl;
                return;
            }
            
        }
    }

    while (!ops.empty()) {
        string val2 = values.top();
        values.pop();

        string val1 = values.top();
        values.pop();

        string op = ops.top();
        ops.pop();

        ApplyOperation(val1, val2, op, variables);
        values.push("temp");
    }

    if (hasOnlyStandardArgument) cout << *variables[values.top()];
    else variables[consoleArgs.back()] = variables["temp"];

    variables.erase("temp");
}

string ComplexOperation::GetName() const
{
    return "complex";
}

string ComplexOperation::GetDescription() const
{
    return "Using this operation you can construct multiple operations at once";
}
