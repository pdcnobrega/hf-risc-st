#include <hf-risc.h>
#include <hf-unit.h>

// function under test
int sort(int v[], int e);

// list of individual tests
void inorder_test();
void equal_test();
void one_element();
void smaller_size(); 

// place here a nice description for each test
void inorder_test(){		
	int v[3] = {0, 1, 2};
	int expected[3] = {0, 1, 2};
	sort(v,3);

	hfunit_assert(
		hfunit_veccomp(v, expected, sizeof(int) * 3),
		"in order vector");
}
//testa vetor com apenas um elemento.
void one_element (){
	int v[1] = {7};
	int expected[1] = {7};
	sort(v,1);
	
	hfunit_assert(
                hfunit_veccomp(v, expected, sizeof(int) * 1),
                "one element vector");
}

//testa função sort ao receber como parâmetro tamanho menor do que o do vetor
void smaller_size (){
	int v[3] = {2, 1, 0};
	int expected[3] = {1, 2, 0};
	sort(v,2);

	hfunit_assert(
                hfunit_veccomp(v, expected, sizeof(int) * 3),
                "partial sort");
}

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
	one_element();
	smaller_size();	
}
