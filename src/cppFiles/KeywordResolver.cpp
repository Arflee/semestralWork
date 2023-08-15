#include "OperationBuilder.h"
#include "KeywordResolver.h"

void KeywordResolver::Resolve(const string& consoleArg)
{
    auto allOperations = OperationBuilder::GetAllOperations();

    for (size_t i = 0; i < allOperations.size(); i++)
    {
        if (consoleArg == "temp")
        {
            isGood = false;
            break;
        }
        

        if (isFirstWord && allOperations[i]->GetName() == consoleArg)
        {
            isFirstWord = false;
            break;
        }
        else if (!isFirstWord && allOperations[i]->GetName() == consoleArg)
        {
            isGood = false;
            break;
        }
    }
}