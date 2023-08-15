#pragma once

#include "Operation.h"

/**
 * @brief Operation for loading all saved variables from file to calculator's variable map
*/
class FileLoadOperation : public Operation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};