
#define TEST_ISL
#ifdef TEST_ISL
#include "test_isl.hpp"
#endif
int main () {
#ifdef TEST_ISL
    Test test;
    test.test_isl();
#endif
    return 0;
}  