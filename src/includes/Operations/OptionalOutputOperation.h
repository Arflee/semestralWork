#pragma once

#include "Operation.h"

/**
 * @brief Abstract class for operations with optional arguments.
 * Recommended to use HandleErrors method for setting bool variable depending on arguments count
 * and then use it in HandleOperation method.
 * 
 * If optional argument is set then result saved to output matrix variable
*/
class OptionalOutputOperation : public Operation
{
protected:
	bool hasOnlyStandardArgument = false;

public:
	virtual bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) = 0;
	virtual void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) = 0;
	virtual string GetName() const = 0;
	virtual string GetDescription() const = 0;
};