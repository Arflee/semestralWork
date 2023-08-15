#pragma once

#include "Operation.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Operation for outputing all available operations to user.
 * Uses GetName and GetDescription from every operation in the global repository
*/
class HelpOperation : public Operation
{
public:
    bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
    void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;

    string GetName() const override;
    string GetDescription() const override;
};

