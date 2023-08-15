#pragma once

#include <string>
#include <memory>
#include <map>
#include "Matrix.h"
#include "OperationBuilder.h"

using namespace std;

/**
 * @brief Class used to parse all entered arguments by user.
 * If was found a bad keyword, the error message will be displayed
*/
class KeywordResolver
{
private:
	bool isGood = true;
	bool isFirstWord = true;

public:
	void Resolve(const string& consoleArg);
	bool IsGood() { return isGood; }
};
