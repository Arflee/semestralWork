SRCPATH=./src
HEADERS = $(wildcard src/*.h)
TESTS = $(wildcard tests/*.test.cpp)
PATHTOHEADERS=$(SRCPATH)/includes
PATHTOCPP=$(SRCPATH)/cppFiles
OPERATIONSPATH=$(PATHTOCPP)/Operations
CXX=g++
CXXFLAGS=-Wall -MMD -pedantic -std=c++17 -I$(PATHTOHEADERS) -I$(PATHTOHEADERS)/Operations

OBJECTS=$(PATHTOCPP)/main.o $(PATHTOCPP)/Matrix.o $(PATHTOCPP)/SparseMatrix.o $(PATHTOCPP)/DenseMatrix.o $(OPERATIONSPATH)/Operation.o \
$(PATHTOCPP)/OperationBuilder.o $(OPERATIONSPATH)/AddOperation.o $(OPERATIONSPATH)/HelpOperation.o \
$(OPERATIONSPATH)/InputOperation.o $(OPERATIONSPATH)/CoefficientMultiplyOperation.o $(OPERATIONSPATH)/ListOperation.o \
$(OPERATIONSPATH)/ExitOperation.o $(OPERATIONSPATH)/SubtractOperation.o $(OPERATIONSPATH)/TranspositionOperation.o \
$(OPERATIONSPATH)/PrintOperation.o $(OPERATIONSPATH)/GaussianEliminationOperation.o \
$(OPERATIONSPATH)/MatrixMultiplyOperation.o $(OPERATIONSPATH)/RankOperation.o \
$(OPERATIONSPATH)/DeterminantOperation.o $(OPERATIONSPATH)/InverseOperation.o \
$(OPERATIONSPATH)/MergeOperation.o $(OPERATIONSPATH)/DivisionOperation.o $(OPERATIONSPATH)/CutOperation.o \
$(OPERATIONSPATH)/FileSaveOperation.o $(OPERATIONSPATH)/FileLoadOperation.o $(OPERATIONSPATH)/FileLoadOperation.o \
$(OPERATIONSPATH)/ComplexOperation.o $(PATHTOCPP)/MatrixLoader.o $(PATHTOCPP)/KeywordResolver.o

run: compile 
	./sushimat

all: compile doc

compile: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o ./sushimat $^

$(SRCPATH)/%.o: $(PATHTOCPP)/%.cpp
	$(CXXFLAGS) $< -c -o $@

clean:
	rm -rf debug $(OPERATIONSPATH)/*.d $(PATHTOCPP)/*.d sushimat ./doc $(PATHTOCPP)/*.o $(OPERATIONSPATH)/*.o

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

debug/%.test: tests/%.test.cpp $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@ $^

test_all: $(TESTS:tests/%.test.cpp=debug/%.test)
	for TEST in debug/*.test; do ./$$TEST; done