#pragma once

#include "OptionalOutputOperation.h"
/**
 * @brief Operation for multiplying two matrices together
*/
class MatrixMultiplyOperation : public OptionalOutputOperation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;

};