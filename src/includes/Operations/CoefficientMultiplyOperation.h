#pragma once

#include "OptionalOutputOperation.h"
#include "Matrix.h"
#include <memory>

/**
   * @brief Class for multiplying matrix with scalar value
   */
class CoefficientMultiplyOperation : public OptionalOutputOperation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};