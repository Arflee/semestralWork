#pragma once

#include <filesystem>
#include "Operation.h"

namespace fs = std::filesystem;

/**
 * @brief Operation for saving all variables from calculator's map to text file
*/
class FileSaveOperation : public Operation
{
private:
	fs::path currentPath = fs::current_path();

public:
	bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
	string GetName() const override;
	string GetDescription() const override;
};