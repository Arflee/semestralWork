#include <iostream>
#include <string>
#include "HelpOperation.h"
#include "Operation.h"
#include "OperationBuilder.h"

using namespace std;

bool HelpOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
	if (consoleArgs.size() > 1)
	{
		cout << "Too many arguments. To see the help menu just type \"help\"" << endl;
		return true;
	}

	return false;
}

void HelpOperation::HandleOperation(vector<string>, map<string, shared_ptr<Matrix>>&)
{
	auto allOperations = OperationBuilder::GetAllOperations();
	cout << endl;
	cout << "Every operation in the calculator starts with its name. Then go all the arguments for the operation" << endl;
	cout << "Arguments written in brackets \"[]\" are optional. Operations with additional arguments will save the result to the entered variable" << endl;
	cout << endl;

	for (size_t i = 0; i < allOperations.size(); i++)
	{
		auto currentOperation = allOperations[i].get();
		cout << currentOperation->GetName() << ": ";
		cout << currentOperation->GetDescription() << endl;

		if (i < allOperations.size() - 1)
		{
			cout << endl;
		}
	}
}

string HelpOperation::GetName() const
{
	return "help";
}

string HelpOperation::GetDescription() const
{
	return "Lists all available matrix operations";
}
