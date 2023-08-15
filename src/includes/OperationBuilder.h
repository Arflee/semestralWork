#pragma once

#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>
#include "Operation.h"
#include "HelpOperation.h"
#include "AddOperation.h"
#include "Matrix.h"

using namespace std;
/**
 * @brief This class searches the operation in static repository.
 * When new operation is created, it has to be added to that repository
*/
class OperationBuilder
{
private:
    static vector<shared_ptr<Operation>> allOperations;
    shared_ptr<Operation> CreateOperation(const string& operationName) const;

public:
    void CallOperation(const vector<string>& consoleArgs,
        map<string, shared_ptr<Matrix>>& variables) const;
    static vector<shared_ptr<Operation>> GetAllOperations();
};