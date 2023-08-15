#pragma once

#include <map>
#include <memory>
#include "Matrix.h"
#include "Operation.h"

/**
 * @brief Operation allows to user enter his own matrices.
 * At the end of operation calculator decides what type of matrix use to store the values depending
 * on values density
*/
class InputOperation : public Operation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;

	string GetName() const override;
	string GetDescription() const override;
};