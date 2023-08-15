#pragma once

#include "OptionalOutputOperation.h"

/**
 * @brief Operation for merging two matrices together into bigger one.
 * User can choose from what side to merge
*/
class MergeOperation : public OptionalOutputOperation
{
private:
	void ToLower(string& str) const;
	bool hasDirection;

public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};
