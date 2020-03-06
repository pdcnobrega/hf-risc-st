#include <hf-risc.h>
#include <hf-unit.h>

// function under test
int sort(int v[], int e);

// list of individual tests
void inorder_test(char* msg);
void equal_test(char* msg);
void one_element(char* msg);
void smaller_size(char* msg); 

// place here a nice description for each test
void inorder_test(char* msg){		
	int v[3] = {0, 1, 2};
	int expected[3] = {0, 1, 2};
	sort(v,3);

	hfunit_assert(hfunit_veccomp(v, expected, sizeof(int) * 3),msg);
}
//testa vetor com apenas um elemento.
void one_element (char* msg){
	int v[1] = {7};
	int expected[1] = {7};
	sort(v,1);
	
	hfunit_assert(hfunit_veccomp(v, expected, sizeof(int) * 1),msg);
}

//testa função sort ao receber como parâmetro tamanho menor do que o do vetor
void smaller_size (char* msg){
	int v[3] = {2, 1, 0};
	int expected[3] = {1, 2, 0};
	sort(v,2);

	hfunit_assert(hfunit_veccomp(v, expected, sizeof(int) * 3),msg);
}

void equal_test(char* msg){

	int v[3] = {1, 1, 1};
	int expected[3] = {1, 1, 1};
	sort(v,3);
	
	hfunit_assert(hfunit_veccomp(v, expected, sizeof(int) * 3),msg);
}

// main test

void mat_test (){
	inorder_test("in order vector");
	equal_test("vector filled with the same values");
	one_element("one element vector");
	smaller_size("partial sort");
}
void hfunit_test() {
	mat_test();
}
