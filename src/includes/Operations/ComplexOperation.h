#pragma once

#include "OptionalOutputOperation.h"
#include "OperationBuilder.h"

using namespace std;

/**
   * @brief Class for combining several operations at once.
   * At the moment supported operations are: adding, subtracting,
   * scalar multiplying, matrix multiplying
   */
class ComplexOperation : public OptionalOutputOperation
{
private:
/**
 * Method for computing intermediate result
 * @param firstMat
 * @param secondMat
 * @param operation
 * @param variables
 * @return intermediate matrix for further calculation
*/
	shared_ptr<Matrix> ApplyOperation(string& firstMat, string& secondMat, string& operation,
		map<string, shared_ptr<Matrix>>& variables) const
	{
		OperationBuilder opBuilder;
		opBuilder.CallOperation({operation, firstMat, secondMat, "temp"}, variables);
		auto& temp = variables["temp"];
		return temp;
	}

	int GetOperationPrecedence(string& operation) const
	{
		if (operation == "mmul")
			return 2;
		else if (operation == "add" || operation == "sub")
			return 1;
		else
			return 0;
	}

	bool IsOperation(string& opName) const
	{
		auto allOperations = OperationBuilder::GetAllOperations();
		for (size_t i = 0; i < allOperations.size(); i++)
		{
			if (opName == allOperations[i]->GetName())
			{
				return true;
			}
		}
		
		return false;
	}

public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};