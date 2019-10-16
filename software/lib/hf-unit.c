#include<hf-unit.h>

/*** **********************************************************
 * 
 * HF-RISC Unit Testing framework 
 * 
 * -> edit these macroses below to set the behavior of HF-UNIT
 * -> see usage examples in the dir software/tests 
 * 
 ************************************************************ */

/** number of executed tests. **/
int _hfunit_counter_total_tests;

/** number of tests that passed. **/
int _hfunit_counter_passed_tests;

/** number of tests that failed. **/
int _hfunit_counter_failed_tests;

/**
 * @brief Asserts a condition and prints respective messages. 
 * @param condition to be asserted, must be a boolean expression
 * @param assertion_name a name to appear in the printed message 
 */ 
void hfunit_assert(int condition, char* assertion_name){
	
	if(!condition){
		HFUNIT_MSG_FAIL(assertion_name);
		_hfunit_counter_failed_tests++;
	}else{ 
		HFUNIT_MSG_PASS(assertion_name);
		_hfunit_counter_passed_tests++;
	}
	
	_hfunit_counter_total_tests++;
}

/**
 * @brief Reset internal counters and starts a new test session.
 */
void hfunit_init(){
	_hfunit_counter_total_tests  = 0;
	_hfunit_counter_passed_tests = 0;
	_hfunit_counter_failed_tests = 0;	
}

/**
 * @brief Entry-point for the unit framework, replaces "main"
 * @param argc optional number of arguments
 * @param argv optional array of arguments
 * @return status code 
 */
int main_test(int argc, char** argv){
	hfunit_init();
	
	HFUNIT_MSG("====================================[HFUNIT]");
	hfunit_test();
	hfunit_report();
	
	HFUNIT_MSG(
		!hfunit_get_test_failed() 
			? "TEST SET PASSED!"
			: "TEST SET FAILED!"
	);
	
	HFUNIT_MSG("============================================");
	
	//returns status to upper level
	return hfunit_get_test_failed();
}

/**
 * @brief Report test statistics ifdef HFUNIT_VERBOSE
 */
void hfunit_report(){

	HFUNIT_MSG("====================================[REPORT]");
	HFUNIT_MSG_P1("total executed tests", hfunit_get_test_count());
	HFUNIT_MSG_P1("tests passed", hfunit_get_test_passed());
	HFUNIT_MSG_P1("tests failed", hfunit_get_test_failed());
	HFUNIT_MSG("============================================");
}

/**
 * @brief Getter for the number of executed tests.
 * @return The number of tests that passed since the last call of hfunit_init().
 */
uint32_t hfunit_get_test_count(){
	return _hfunit_counter_total_tests;
}

/**
 * @brief Getter for the number of tests that passed.
 * @return The number of tests that were executed since the last call of hfunit_init().
 */
uint32_t hfunit_get_test_passed(){
	return _hfunit_counter_passed_tests;
}

/**
 * @brief Getter for the number of tests that failed.
 * @return The number of tests that failed since the last call of hfunit_init().
 */
uint32_t hfunit_get_test_failed(){
	return _hfunit_counter_failed_tests;
}

//auxiliary functions
/**
 * @brief Compare two vectors of integer types
 * @param v1 the first vector
 * @param v2 the second vector
 * @param size the size of both vectors
 * @return the number of elements unique to some vector
 */
int hfunit_veccomp(void* v1, void* v2, uint32_t size){
	return memcmp(v1,v2,size) == 0;
}

/**
 * @brief Compare two vectors of floats
 * @param v1 the first vector
 * @param v2 the second vector
 * @param size the size of both vectors
 * @return the number of elements unique to some vector
 */
int hfunit_comp_f(float f1, float f2, uint32_t size){
	return (((f1 - HFUNIT_PRECISION) < f2) && ((f1 + HFUNIT_PRECISION) > f2));
}

// =======================
// util functions
// =======================
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
