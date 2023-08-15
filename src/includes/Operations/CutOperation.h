#pragma once

#include "OptionalOutputOperation.h"

/**
 * @brief Class for cutting rectangular part from existing matrix
*/
class CutOperation : public OptionalOutputOperation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	/**
	 * As input method takes matrix and two points for left upper corner and right bottom corner accordingly
	 * @return new matrix which was constructed from calculated area
	*/
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};