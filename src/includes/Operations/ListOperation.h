#pragma once

#include "Operation.h"

/**
 * @brief Operation for displaying all available matrix variables.
 * The output is the same for different types of matrices 
*/
class ListOperation : public Operation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};
