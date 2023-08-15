#pragma once

#include "Operation.h"
/**
 * @brief Operation for calculating determinant of a matrix in variables table
*/
class DeterminantOperation : public Operation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};
