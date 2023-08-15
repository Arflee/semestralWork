#include "Operation.h"

bool Operation::IsNumber(const string& s) const
{
	double ld;
	return ((std::istringstream(s) >> ld >> std::ws).eof());
}

bool Operation::CheckMatrix(string argument, map<string, shared_ptr<Matrix>>& variables) const
{
	auto& matrix = variables[argument];
	return matrix != nullptr;
}

void Operation::Execute(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables)
{
	if (HandleErrors(consoleArgs, variables)) return;

	HandleOperation(consoleArgs, variables);
}
