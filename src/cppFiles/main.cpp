#include <string>
#include <memory>
#include <iostream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>
#include <map>
#include "Matrix.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include "Operation.h"
#include "OperationBuilder.h"
#include "ExitOperation.h"
#include "KeywordResolver.h"

using namespace std;

int main()
{
    string mainName = R"(
                    _          _                     _               _         _               
                   | |        (_)                   | |             | |       | |              
  _ __ ___    __ _ | |_  _ __  _ __  __   ___  __ _ | |  ___  _   _ | |  __ _ | |_  ___   _ __ 
 | '_ ` _ \  / _` || __|| '__|| |\ \/ /  / __|/ _` || | / __|| | | || | / _` || __|/ _ \ | '__|
 | | | | | || (_| || |_ | |   | | >  <  | (__| (_| || || (__ | |_| || || (_| || |_| (_) || |   
 |_| |_| |_| \__,_| \__||_|   |_|/_/\_\  \___|\__,_||_| \___| \__,_||_| \__,_| \__|\___/ |_|   
                                                                                               
                                                                                               
)";

    SparseMatrix sp(3, 3);
    cout << mainName << endl << endl;
    cout << "Write \"help\" to see all available matrix operations" << endl;

    string input;
    OperationBuilder opBuilder;
    map<string, shared_ptr<Matrix>> variables;

    while (cin && getline(cin, input))
    {
        if (input == ExitOperation::GetExitString()) return 0;

        stringstream ss(input);
        vector<string> consoleArgs;
        KeywordResolver resolver;

        while (ss.good())
        {
            string temp;
            ss >> temp;
            if (temp.size() > 0)
            {
                // check if entered word is a keyword
                if (consoleArgs.size() > 0 && consoleArgs[0] != "complex")
                {
                    resolver.Resolve(temp);
                }
                consoleArgs.push_back(temp);
            }
        }

        if (!resolver.IsGood())
        {
            cout << "You've entered keyword as argument name. Try one more time with different name" << endl;
            continue;
        }

        if (consoleArgs.size() > 0)
        {
            opBuilder.CallOperation(consoleArgs, variables);
            cout << endl;
        }
    }
}