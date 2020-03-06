#include "../../include/hf-risc.h"
#include "../../include/hf-unit.h"

// function under test 
float sqrt(float arg);


// list of individual tests
void sqrt1_test(char* msg);
void sqrt4_test(char* msg);


// place here a nice description for each test
void sqrt1_test(char* msg){
	float v = sqrt(1.0);
	float expected = 1.0;
	
	hfunit_assert(hfunit_comp_f(v, expected, HFUNIT_PRECISION),msg);
}

// place here a nice description for each test
void sqrt4_test(char* msg){
	float v = sqrt(4.0);
	float expected = 2.0;
	
	hfunit_assert(hfunit_comp_f(v, expected, HFUNIT_PRECISION),msg);
}

// main test
void mat_test(){
	sqrt1_test("sqrt(1.0)");
	sqrt4_test("sqrt(4.0)");
}

//main test
void hfunit_test() {
	mat_test();
}
