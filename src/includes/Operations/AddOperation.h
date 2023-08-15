#pragma once

#include <memory>
#include <map>
#include "OptionalOutputOperation.h"
#include "Matrix.h"

using namespace std;

/**
   * @brief Class for adding two matrices together
*/
class AddOperation : public OptionalOutputOperation
{
public:
    bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
    void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) override;
    string GetName() const override;
    string GetDescription() const override;

};