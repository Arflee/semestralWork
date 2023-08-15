#include "CoefficientMultiplyOperation.h"

bool CoefficientMultiplyOperation::HandleErrors(vector<string> consoleArgs,
	map<string, shared_ptr<Matrix>>&)
{
	if (consoleArgs.size() < 3)
	{
		cout << "ERROR: Something is missing in the arguments, please, try one more time" << endl;
		return true;
	}
	else if (consoleArgs.size() > 4)
	{
		cout << "ERROR: Too many arguments, the semantics are: mul SCALAR MATRIX_NAME [OUTPUT_NAME]" << endl;
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

void CoefficientMultiplyOperation::HandleOperation(vector<string> consoleArgs,
	map<string, shared_ptr<Matrix>>& variables)
{
	if (!IsNumber(consoleArgs[1]))
	{
		cout << "ERROR: The scalar constant must be a number" << endl;
		return;
	}
	double coefficient = stod(consoleArgs[1]);

	auto& matrix = variables[consoleArgs[2]];
	if (matrix == nullptr)
	{
		cout << "ERROR: The given matrix were not found in the variables" << endl;
		return;
	}


	auto newMatrix = *matrix * coefficient;
	if (hasOnlyStandardArgument)
	{
		cout << *newMatrix;
		return;
	}

	variables[consoleArgs[3]] = newMatrix;
}

string CoefficientMultiplyOperation::GetName() const
{
	return "mul";
}

string CoefficientMultiplyOperation::GetDescription() const
{
	return "mul SCALAR MATRIX_NAME\n Multiplies matrix with constant coefficient";
}
