#pragma once

#include "Operation.h"

/**
 * @brief Operation for displaying a single available matrix from variables map
 * The output is the same for different types of matrices 
*/
class PrintOperation : public Operation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};