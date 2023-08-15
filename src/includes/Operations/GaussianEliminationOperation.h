#pragma once

#include "OptionalOutputOperation.h"

/**
 * @brief Operation for finding matrix after all Gauss–Jordan elimination steps
*/
class GaussianEliminationOperation : public OptionalOutputOperation
{
public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	/**
	 * @return Matrix in upper triangular form which solves homogeneous equation
	*/
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;

};