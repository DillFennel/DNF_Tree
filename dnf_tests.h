#ifndef DNF_TESTS
#define DNF_TESTS

void test_degree_of_two();
void test_dnf();
void test_two_not();
void test_three_not();
void test_three_inversions_2();
void test_three_inversions_3();
void test_three_inversions_4();
void test_three_inversions_5();
void test_tree_optimization();
void test_many();

bool run_tests(){
    test_degree_of_two();
    test_dnf();
    test_two_not();
    test_three_not();
    test_three_inversions_2();
    test_three_inversions_3();
    test_three_inversions_4();
    test_three_inversions_5();
    test_tree_optimization();
    test_many();
    return true;
}
 
#endif