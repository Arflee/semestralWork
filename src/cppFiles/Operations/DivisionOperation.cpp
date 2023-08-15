#include "DivisionOperation.h"

bool DivisionOperation::HandleErrors(vector<string> consoleArgs,
	map<string, shared_ptr<Matrix>>&)
{
	if (consoleArgs.size() < 3)
	{
		cout << "ERROR: Something is missing in the arguments, please, try one more time" << endl;
		return true;
	}
	else if (consoleArgs.size() > 4)
	{
		cout << "ERROR: Too many arguments, the semantics are: div SCALAR MATRIX_NAME [OUTPUT_NAME]" << endl;
		return true;
	}
	else if (consoleArgs.size() == 3)
	{
		hasOnlyStandardArgument = true;
		return false;
	}

	hasOnlyStandardArgument = false;
	return false;
}

void DivisionOperation::HandleOperation(vector<string> consoleArgs,
	map<string, shared_ptr<Matrix>>& variables)
{
	if (!IsNumber(consoleArgs[1]))
	{
		cout << "ERROR: The scalar constant must be a number" << endl;
		return;
	}
	double coefficient = 1 / stod(consoleArgs[1]);

	auto& matrix = variables[consoleArgs[2]];
	if (matrix == nullptr)
	{
		cout << "ERROR: The given matrix were not found in the variables" << endl;
		return;
	}

    auto output =  (*matrix) * coefficient;
	if (hasOnlyStandardArgument)
	{
		cout << *output;
		return;
	}

	variables[consoleArgs[3]] = output;
}

string DivisionOperation::GetName() const
{
    return "div";
}

string DivisionOperation::GetDescription() const
{
	return "div SCALAR MATRIX_NAME\n Divides matrix by constant coefficient";
}
