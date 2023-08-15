#pragma once

#include "OptionalOutputOperation.h"

/**
 * @brief Operation for finding inverse matrix.
 * To find inverse matrix used the formula A^(-1) = adj(A) / |A|
*/
class InverseOperation : public OptionalOutputOperation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};
