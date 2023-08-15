#include <cassert>
#include "DenseMatrix.h"

int main()
{
    DenseMatrix a = {{1,2,3}, {3,4,5}};
    DenseMatrix b = {{1,2,3}};
    assert((a * b) == nullptr);
}