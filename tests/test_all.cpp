#include "test_suite.h"
#include "tests.h"

int main( void )
{
	testing::Tester t;

	testMatrix(t);
	testVector(t);

	t.test();

	return 0;
}
