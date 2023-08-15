#include "OperationBuilder.h"
#include "CoefficientMultiplyOperation.h"
#include "AddOperation.h"
#include "ListOperation.h"
#include "InputOperation.h"
#include "ExitOperation.h"
#include "MatrixMultiplyOperation.h"
#include "SubtractOperation.h"
#include "TranspositionOperation.h"
#include "PrintOperation.h"
#include "GaussianEliminationOperation.h"
#include "RankOperation.h"
#include "DeterminantOperation.h"
#include "InverseOperation.h"
#include "MergeOperation.h"
#include "DivisionOperation.h"
#include "CutOperation.h"
#include "FileSaveOperation.h"
#include "ComplexOperation.h"
#include "FileLoadOperation.h"

vector<shared_ptr<Operation>> OperationBuilder::allOperations =
{
	shared_ptr<HelpOperation>(new HelpOperation()),
	shared_ptr<InputOperation>(new InputOperation()),
	shared_ptr<ListOperation>(new ListOperation()),
	shared_ptr<PrintOperation>(new PrintOperation()),
	shared_ptr<AddOperation>(new AddOperation()),
	shared_ptr<SubtractOperation>(new SubtractOperation()),
	shared_ptr<CoefficientMultiplyOperation>(new CoefficientMultiplyOperation()),
	shared_ptr<DivisionOperation>(new DivisionOperation()),
	shared_ptr<MergeOperation>(new MergeOperation()),
	shared_ptr<CutOperation>(new CutOperation()),
	shared_ptr<MatrixMultiplyOperation>(new MatrixMultiplyOperation()),
	shared_ptr<TranspositionOperation>(new TranspositionOperation()),
	shared_ptr<GaussianEliminationOperation>(new GaussianEliminationOperation()),
	shared_ptr<RankOperation>(new RankOperation()),
	shared_ptr<DeterminantOperation>(new DeterminantOperation()),
	shared_ptr<InverseOperation>(new InverseOperation()),
	shared_ptr<FileSaveOperation>(new FileSaveOperation()),
	shared_ptr<FileLoadOperation>(new FileLoadOperation()),
	shared_ptr<ComplexOperation>(new ComplexOperation()),
	shared_ptr<ExitOperation>(new ExitOperation()),
};


shared_ptr<Operation> OperationBuilder::CreateOperation(const string& operationName) const
{
	for (size_t i = 0; i < allOperations.size(); i++)
		if (allOperations[i]->GetName() == operationName)
			return allOperations[i];

	return nullptr;
}

void OperationBuilder::CallOperation(const vector<string>& consoleArgs,
	map<string, shared_ptr<Matrix>>& variables) const
{
	auto createdOp = CreateOperation(consoleArgs[0]);

	if (createdOp == nullptr)
	{
		cout << "No such operation" << endl;
		return;
	}

	createdOp->Execute(consoleArgs, variables);
}

vector<shared_ptr<Operation>> OperationBuilder::GetAllOperations()
{
	return allOperations;
}
