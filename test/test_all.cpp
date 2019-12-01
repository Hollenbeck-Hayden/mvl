#include "test_suite.h"
#include "tests.h"

int main( void )
{
	testing::Tester t;

	testDataMatrix(t);
	testAbstractVector(t);
	testMatrix(t);

	t.test();

	return 0;
}
