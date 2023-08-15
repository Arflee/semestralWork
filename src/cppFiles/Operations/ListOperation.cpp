#include <iostream>
#include <string>
#include "ListOperation.h"

using namespace std;

bool ListOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
	if (consoleArgs.size() > 1)
	{
		cout << "Too many arguments. To see the variables just type \"list\"" << endl;
		return true;
	}

    return false;
}

void ListOperation::HandleOperation(vector<string>, map<string, shared_ptr<Matrix>>& variables)
{
	cout << endl;

	if (variables.size() == 0)
	{
		cout << "<empty>" << endl;;
		return;
	}

	for (auto it = variables.begin(); it != variables.end(); ++it)
	{
		if (it->second != nullptr)
		{
			cout << it->first << ":" << endl;
			cout << (*it->second);

			auto temp = it;
			if (++temp != variables.end())
			{
				cout << endl;
			}
		}
	}
}

string ListOperation::GetName() const
{
    return "list";
}

string ListOperation::GetDescription() const
{
    return "Lists all defined matrix variables";
}
