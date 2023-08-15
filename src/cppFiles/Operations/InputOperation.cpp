#include "InputOperation.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include <map>

bool InputOperation::HandleErrors(vector<string> consoleArgs, map<string, shared_ptr<Matrix>>&)
{
	if (consoleArgs.size() < 2)
	{
		cout << "Please write variable where to store you matrix" << endl;
		return true;
	}
	else if (consoleArgs.size() > 2)
	{
		cout << "Too many arguments, the semanitcs are: input VARIABLE_NAME" << endl;
		return true;
	}

	return false;
}

void InputOperation::HandleOperation(vector<string> consoleArgs,
	map<string, shared_ptr<Matrix>>& variables)
{
	string heightStr, widthStr;
	cout << "Enter matrix size (h, w): " << endl;
	cin >> heightStr >> widthStr;

	if (!IsNumber(heightStr) || !IsNumber(widthStr))
	{
		cout << "ERROR: You have to write size as two numbers" << endl;
		return;
	}

	int height, width;
	height = stoi(heightStr);
	width = stoi(widthStr);

	if (height <= 0 || width <= 0)
	{
		cout << "ERROR: Size must be bigger than 0" << endl;
		return;
	}

	cout << endl << "Now write matrix elements:" << endl;
	DenseMatrix inputMatrix(height, width);

	int zeroCounter = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			string elementStr;
			cin >> elementStr;

			if (!IsNumber(elementStr))
			{
				cout << "ERROR: Something went wrong" << endl;
				return;
			}

			double element = stod(elementStr);
			if (element == 0) zeroCounter++;

			inputMatrix.Set(i, j, element);
		}
	}

	string matrixName = consoleArgs[1];
	string dummyString;
	getline(cin, dummyString);

	shared_ptr<Matrix> savedMatrix;

	if (zeroCounter >= (height * width) / 2)
	{
		savedMatrix = shared_ptr<Matrix>(new SparseMatrix(inputMatrix));
	}
	else
	{
		savedMatrix = shared_ptr<Matrix>(new DenseMatrix(inputMatrix));
	}

	variables[matrixName] = savedMatrix;
	cout << "Done!" << endl;
}

string InputOperation::GetName() const
{
	return "input";
}

string InputOperation::GetDescription() const
{
	return "input MATRIX_NAME\n Creates matrix from user input";
}
