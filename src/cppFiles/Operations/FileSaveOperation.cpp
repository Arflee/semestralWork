#include <fstream>
#include <iostream>
#include <filesystem>
#include "FileSaveOperation.h"

namespace fs = std::filesystem;

bool FileSaveOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
    if (consoleArgs.size() > 1)
    {
        cout << "ERROR: Too many arguments. To save variables write \"save\"";
        return true;
    }

    return false;
}

void FileSaveOperation::HandleOperation(vector<string>, map<string, shared_ptr<Matrix>>& variables)
{
    currentPath /= "save.txt";

    ofstream saveFile(currentPath, ios::out);
    currentPath = fs::current_path();

    if (!saveFile)
    {
        cout << "ERROR: Cannot open save file!" << endl;
        return;
    }

    for (auto it = variables.begin(); it != variables.end(); ++it)
    {
        it->second->SaveToFile(saveFile, it->first);

        auto temp = it;
        if (++temp != variables.end())
        {
            saveFile << endl;
        }
    }

    saveFile.close();

    if (saveFile.fail())
    {
        cout << "ERROR: Something went wrong";
    }
    
    cout << "Done!";
}

string FileSaveOperation::GetName() const
{
    return "save";
}

string FileSaveOperation::GetDescription() const
{
    return "Saves all variables to txt file keeping calculator semantics";
}
