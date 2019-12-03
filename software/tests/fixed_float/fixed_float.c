#include "../../include/fixed.h"
#include "../../include/hf-unit.h"
int executed_tests=0;
int failed_tests=0;

// funcao para comparação
void assert1(int test, const char * message){
        if (test == 0) {
                printf("Erro: %s\n", message);
                failed_tests++;
        }
        executed_tests++;
}

//Função cosseno
void fix_cos_test(fixed_t entrada,fixed_t esperado,char* msg){
	fixed_t saida;
	saida=fix_cos(entrada);
	fixed_t arred = saida - esperado;
	assert1(arred<0.000001||arred>0.000001,msg);
}
//Função seno
void fix_sin_test(fixed_t entrada,fixed_t esperado,char* msg){
        fixed_t saida;
        saida=fix_sin(entrada);
	fixed_t arred = saida - esperado;
        assert1(arred<0.000001||arred>0.000001,msg); 
}
/*
Recebe valor de entrada, eleva a constante 'e' ao valor de entrada, atribui o
resultado à variável saida e compara a saida com valor esperado.

*/
void fix_exp_test(fixed_t entrada,fixed_t esperado,char* msg){
        fixed_t saida;
        saida=fix_exp(entrada);
	fixed_t arred = saida - esperado;
        assert1(arred<0.000001||arred>0.000001,msg);
}
/*
Calcula a raiz quadrada do valor de entrada, atribui o resultado à variável saída
e compara o valor da saída com o valor esperado.
*/
void fix_sqrt_test(fixed_t entrada, fixed_t esperado, char* msg){
	fixed_t saida;
	saida=fix_sqrt(entrada);
	fixed_t arred = saida - esperado;
        assert1(arred<0.000001||arred>0.000001,msg);
}

// função testada sera a fix_logaritmo
fixed_t fix_log(fixed_t fp, fixed_t base);


void teste1(){
	fixed_t input = fix_val(5.5f);
        // atribuicao do valor fixed a funcao fix_ln
        fixed_t result = fix_log(input,10);

        int8_t buf[30];
        fixtoa(result, buf, 6);

        assert1(buf[0] == '1' && buf[1] == '.' && buf[2] == '7' && buf[3] == '0', "Log de 1.5f deve ser aproximadamente 1.704748");
}
void test_tamanho() {
	fixed_t test_tam = pow (2,FIX_IBITS);
	
	assert1(test_tam<fix_val(472700090348091277312),"número muito grande");
}

float testfloat_add(float min, float max, float step)
{
	float i, s = 0.0;
	
	for (i = min; i < max; i += step)
		s += step;
	
	return s;
}

fixed_t testfixed_add(fixed_t min, fixed_t max, fixed_t step)
{
	fixed_t i, s = fix_val(0.0);
	
	for (i = min; i < max; i += step)
		s += step;
	
	return s;
}

float testfloat_sub(float min, float max, float step)
{
	float i, s = 0.0;
	
	for (i = max; i >= min; i -= step)
		s -= step;

	return s;
}

fixed_t testfixed_sub(fixed_t min, fixed_t max, fixed_t step)
{
	fixed_t i, s = fix_val(0.0);
	
	for (i = max; i >= min; i -= step)
		s -= step;
	
	return s;
}

float testfloat_mul(float min, float max, float step)
{
	float i, s = max;
	
	for (i = min; i < max; i += step)
		s *= 1.000001;
	
	return s;
}

fixed_t testfixed_mul(fixed_t min, fixed_t max, fixed_t step)
{
	fixed_t i, s = max;
	
	for (i = min; i < max; i += step)
		s = fix_mul(s, fix_val(1.000001));
	
	return s;
}

float testfloat_div(float min, float max, float step)
{
	float i, s = max;
	
	for (i = min; i < max; i += step)
		s /= 1.000001;
	
	return s;
}

fixed_t testfixed_div(fixed_t min, fixed_t max, fixed_t step)
{
	fixed_t i, s = max;
	
	for (i = min; i < max; i += step)
		s = fix_div(s, fix_val(1.000001));
	
	return s;
}

void assert(int test, const char * message){
        if (test == 0) {
                printf("Error: %s\n", message);
                failed_tests++;
        }
        executed_tests++;
}

fixed_t test_tan_lower_limit()
{
        fixed_t input = fix_val(1);
        fixed_t result = fix_ln(input);

        int8_t buf[30];
        fixtoa(result, buf, 6);

        assert1(buf[0] == '0' && (buf[1] == '\0' || (buf[2] == '0' && buf[3] == '0')), "natural log of 1 should be as close to zero as possible");
	return result;
}

fixed_t test_tan_implementation_limit()
{
        fixed_t input = fix_val(1.5f);
        fixed_t result = fix_ln(input);

        int8_t buf[30];
        fixtoa(result, buf, 6);

        assert1(buf[0] == '0' && buf[1] == '.' && buf[2] == '4' && buf[3] == '0', "natural log 1.5 should be close to 0.405");
	return result;
}

void fix_tan_test()
{
        test_tan_lower_limit();
        test_tan_implementation_limit();
}
int main()
{
	/* volatile is being used to avoid the optimizer from being too smart */
	volatile float minfl = -1000.0;
	volatile float maxfl = 1000.0;
	volatile float stepfl = 0.1;
	float vfl;
	fixed_t minfx = fix_val(minfl);
	fixed_t maxfx = fix_val(maxfl);
	fixed_t stepfx = fix_val(stepfl);
	fixed_t vfx;
	int8_t buf[20];
	
	printf("\nfloat / fixed point speed test\n");
	vfl = testfloat_add(minfl, maxfl, stepfl);
	ftoa(vfl, buf, 6);
	printf("float add: %s\n", buf);

	vfx = testfixed_add(minfx, maxfx, stepfx);
	fixtoa(vfx, buf, 6);
	printf("fixed add: %s\n", buf);
	
	vfl = testfloat_sub(minfl, maxfl, stepfl);
	ftoa(vfl, buf, 6);
	printf("float sub: %s\n", buf);

	vfx = testfixed_sub(minfx, maxfx, stepfx);
	fixtoa(vfx, buf, 6);
	printf("fixed sub: %s\n", buf);

	vfl = testfloat_mul(minfl, maxfl, stepfl);
	ftoa(vfl, buf, 6);
	printf("float mul: %s\n", buf);

	vfx = testfixed_mul(minfx, maxfx, stepfx);
	fixtoa(vfx, buf, 6);
	printf("fixed mul: %s\n", buf);

	vfl = testfloat_div(minfl, maxfl, stepfl);
	ftoa(vfl, buf, 6);
	printf("float div: %s\n", buf);

	vfx = testfixed_div(minfx, maxfx, stepfx);
	fixtoa(vfx, buf, 6);
	printf("fixed div: %s\n", buf);

        printf("=====================\n");
	printf("natural log of 1: ");
	fix_print(test_tan_lower_limit());
	printf("\n");
	printf("natural log of 1.5: ");
        fix_print(test_tan_implementation_limit());
	printf("\n");

	teste1();
	test_tamanho();

	printf("=====================\n");
	printf("Função exponencial\n");
	fix_exp_test(fix_val(0.0),fix_val(1.0),"Esperado: 1.0");
	fix_exp_test(fix_val(1.0),fix_val(2.718261),"Esperado: 2.718261");
	fix_exp_test(fix_val(2.0),fix_val(7.3890561),"Esperado: 7.3890561");
	fix_exp_test(fix_val(3.0),fix_val(20.085537),"Esperado: 20.085537");
	fix_exp_test(fix_val(22.1807097779),fix_val(4294967295.9999),"Esperado: 4294967295.9999");
	fix_exp_test(fix_val(-1),fix_val(0.36787944117),"Esperado: 0.36787944117");
	fix_exp_test(fix_val(-4294967295.9999),fix_val(0.0),"Esperado: 0.0");
	printf("=====================\n");
        printf("Função raiz quadrada\n");
        fix_sqrt_test(fix_val(0.0),fix_val(0.0),"Esperado: 0.0");
        fix_sqrt_test(fix_val(1.0),fix_val(1.0),"Esperado: 1.0");
        fix_sqrt_test(fix_val(2.0),fix_val(1.41421356237),"Esperado: 1.41421356237");
        fix_sqrt_test(fix_val(22.1807097779),fix_val(4.70964009006),"Esperado: 4.70964009006");
        fix_sqrt_test(fix_val(4294967295.9999),fix_val(65536),"Esperado: 65536");
        fix_sqrt_test(fix_val('a'),fix_val(0.0),"Esperado: erro: entrada não pode ser letra");
        fix_sqrt_test(fix_val(-1.0),fix_val(0.0),"Esperado: erro: entrada não pode ser número negativo");
	printf("=====================\n");
        printf("Função cosseno\n");
        fix_cos_test(fix_val(-FIX_PI),fix_val(-1.0),"Esperado: -1.0");
        fix_cos_test(fix_val(FIX_PI),fix_val(-1.0),"Esperado: -1.0");
        fix_cos_test(fix_val(0.0),fix_val(1.0),"Esperado: 1.0");
        fix_cos_test(fix_val(0.0000001),fix_val(1.0),"Esperado: 1.0");
        fix_cos_test(fix_val(FIX_HALF_PI),fix_val(0.0),"Esperado: 0.0");
        fix_cos_test(fix_val(FIX_FOURTH_PI),fix_val(0.70710678118),"Esperado: 0.70710678118");
        fix_cos_test(fix_val(FIX_TWO_PI),fix_val(1.0),"Esperado: 1.0");
	fix_cos_test(fix_val(2.0),fix_val(-0.41614683654),"Esperado: -0.41614683654");
        printf("=====================\n");
	printf("Função seno\n");
        fix_sin_test(fix_val(-FIX_PI),fix_val(0.0),"Esperado: 0.0");
        fix_sin_test(fix_val(FIX_PI),fix_val(0.0),"Esperado: 0.0");
        fix_sin_test(fix_val(0.0),fix_val(0.0),"Esperado: 0.0");
        fix_sin_test(fix_val(0.0000001),fix_val(0.0),"Esperado: 0.0");
        fix_sin_test(fix_val(FIX_HALF_PI),fix_val(1.0),"Esperado: 1.0");
        fix_sin_test(fix_val(FIX_FOURTH_PI),fix_val(0.707),"Esperado: 0.707");
        fix_sin_test(fix_val(FIX_TWO_PI),fix_val(0.0),"Esperado: 0.0");
        fix_sin_test(fix_val(2.0),fix_val(0.909),"Esperado: 0.909");
	fix_sin_test(fix_val(3*FIX_HALF_PI),fix_val(-1.0),"Esperado: -1.0");

        printf("=====================\n");
        printf("%d tests executed - %d tests failed\n", executed_tests, failed_tests);
        printf("=====================\n");
        if (failed_tests != 0) {
                printf("TEST FAILED !!!\n");
                return 1;
        } else printf("TEST SUCCEEDED !!!\n");
	return 0;
}
