#pragma once

#include "Operation.h"

/**
 * @brief Operation for exiting from main loop and closing calculator
*/
class ExitOperation : public Operation
{
public:
	virtual bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	virtual void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	virtual string GetName() const override;
	virtual string GetDescription() const override;

	static string GetExitString();
};
