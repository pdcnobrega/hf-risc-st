#include <hf-risc.h>
#include <hf-unit.h>

// function under test
int sort(int v[], int e);

// list of individual tests
void inorder_test();
void equal_test();

// place here a nice description for each test
void inorder_test(){
	int v[3] = {0, 1, 2};
	int expected[3] = {0, 1, 2};
	sort(v,3);

	hfunit_assert(
		hfunit_veccomp(v, expected, sizeof(int) * 3),
		"in order vector");
}

// place here a nice description for each test
void equal_test(){

	int v[3] = {1, 1, 1};
	int expected[3] = {1, 1, 1};
	sort(v,3);
	
	hfunit_assert(
		hfunit_veccomp(v, expected, sizeof(int) * 3),
		"vector filled with the same values");
}

// main test
void hfunit_test(){
	inorder_test();
	equal_test();	
}