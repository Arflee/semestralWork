#pragma once

#include "OptionalOutputOperation.h"

/**
 * @brief Operation for finding a rank of a matrix.
 * In the process GEM-like operations are used
*/
class RankOperation : public Operation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};
