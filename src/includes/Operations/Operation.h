#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Matrix.h"

using namespace std;

/**
   * @brief Abstract class for all operations in calculator.
   * The class uses Execute as template method, so every inherited class have to define
   * HandleErros for checking argument amount and
   * HandleOperation for main logic
   */
class Operation
{
protected:
    bool IsNumber(const string& s) const;
    /**
     * Method check whether the key is present in variables
     * @param argument key value
     * @param variables all saved matrices
     * @return true if present in variables / false if not present
    */
    bool CheckMatrix(string argument, map<string, shared_ptr<Matrix>>& variables) const;

public:
    void Execute(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables);
    virtual bool HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) = 0;
    virtual void HandleOperation(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>& variables) = 0;

  /**
   * The name which will be used in calculator
   * @return name of operation to find
   */
    virtual string GetName() const = 0;

    /**
     * HelpOperation uses this description for every operation
     * @return short description with arguments example
    */
    virtual string GetDescription() const = 0;
};
