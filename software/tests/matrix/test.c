/*
This matrix lib can work with 3 different types: fixed, float, and double.
just change the variable MATRIX_TYPE in the makefile
*/

#include <mat_type.h> // this include define the type of the matrix
#include <matrix.h>   // the functions under test are defined here
#include <hf-risc.h>
#include <hf-unit.h>

void transposed_test (char* msg) {
	struct Matrix m;
	struct Matrix transp;
	int erro = 0;
	typ_var val[16] = {val(1),val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16)};

	m  = set_values( 4, 4, val);
	transp  = transposed(m);

	struct Matrix esperada;
	typ_var esp[16] = {val(1),val(5),val(9),val(13),val(2),val(6),val(10),val(14),val(3),val(7),val(11),val(15),val(4),val(8),val(12),val(16)};
	esperada = set_values(4, 4, esp);

	for (int i=0; i<4; i++) {
	    for(int j=0; j<4; j++) {
		if (get_value(transp,i,j)!=get_value(esperada,i,j)) {
			erro = 1;
		}
	    }
	}
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
	print_matrix(transp);
	printf("Esperada:\n");
	print_matrix(esperada);
} 

void sum_matrix_test(char* msg) {
	struct Matrix M1, M2, M3, esperada;
	typ_var val1[16] = {val(1),val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16)};

	typ_var val2[16] = {val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16),val(17)};

	typ_var val3[16] = {val(3),val(5),val(7),val(9),val(11),val(13),val(15),val(17),val(19),val(21),val(23),val(25),val(27),val(29),val(31),val(33)};
	
	M1 = set_values(4, 4, val1);
	M2 = set_values(4, 4, val2);
	esperada = set_values(4, 4, val3);
	M3 = sum(M1, M2);
	
	int erro = 0;

	for (int i=0; i<4; i++) {
                for(int j=0; j<4; j++) {
			float arred = get_value(M3,i,j)-get_value(esperada,i,j);
                        if(arred<-0.000001||arred>0.000001) {
                        	erro = 1;
			}
                }
        }
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}

void subtract_matrix_test(char* msg) {
         struct Matrix M1, M2, M3, esperada;
        typ_var val1[16] = {val(1),val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16)};

        typ_var val2[16] = {val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16),val(17)};
	
	typ_var val3[16] = {val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1),val(-1)};
	M1 = set_values(4, 4, val1);
        M2 = set_values(4, 4, val2);
        esperada = set_values(4, 4, val3);
	M3 = subtraction(M1, M2);
	int erro = 0;
        for (int i=0; i<4; i++) { 
                for(int j=0; j<4; j++) {
			float arred = get_value(M3,i,j)-get_value(esperada,i,j);
                        if(arred<-0.000001||arred>0.000001){ 
				erro = 1;
			}
                }
        }
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}
void mult_matrix_test(char* msg) {
    	struct Matrix M1;
	struct Matrix M2;
	struct Matrix M3;
	struct Matrix esperada;
        typ_var val1[16] = {val(1),val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16)};

        typ_var val2[16] = {val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16),val(17)};

        typ_var val3[16] = {val(100),val(110),val(120),val(130),val(228),val(254),val(280),val(306),val(356),val(398),val(440),val(482),val(484),val(542),val(600),val(658)};
        M1 = set_values(4, 4, val1);
        M2 = set_values(4, 4, val2);
        esperada = set_values(4, 4, val3);
        M3 = multiplication(M1, M2);
        int erro = 0;
   	for (int i=0; i<4; i++) {
        	for(int j=0; j<4; j++) {
			float arred = get_value(M3,i,j)-get_value(esperada,i,j);
                        if(arred<-0.000001||arred>0.000001) {
				erro = 1;
			}
	   	}
        }
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}

void multE_test(char* msg) {
	struct Matrix M1, M3, esperada;
	typ_var Multiplicator =  val(5);

        typ_var val1[16] = {val(1),val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16)};

        typ_var val3[16] = {val(5),val(10),val(15),val(20),val(25),val(30),val(35),val(40),val(45),val(50),val(55),val(60),val(65),val(70),val(75),val(80)};

        M1 = set_values(4, 4, val1);
        esperada = set_values(4, 4, val3);
        M3 = multE(M1, Multiplicator);
        int erro = 0;

        for (int i=0; i<4; i++) {
                for(int j=0; j<4; j++) {
			float arred = get_value(M3,i,j)-get_value(esperada,i,j);
                        if(arred<-0.000001||arred>0.000001) {
				erro = 1;
			}
                }
        }
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}

void divE_test(char* msg) {
        struct Matrix M1, M3, esperada;
        typ_var Multiplicator =  val(5);

        typ_var val1[16] = {val(1),val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16)};

        typ_var val3[16] = {val(0.199),val(0.339),val(0.6),val(0.8),val(1),val(1.2),val(1.399),val(1.6),val(1.79),val(2),val(2.2),val(2.4),val(2.59),val(2.79),val(3),val(3.2)};

        M1 = set_values(4, 4, val1);
        esperada = set_values(4, 4, val3);
        M3 = divE(M1, Multiplicator);
	int erro = 0;
	
        for (int i=0; i<4; i++) {
                for(int j=0; j<4; j++) {
			float arred = get_value(M3,i,j)-get_value(esperada,i,j);
			if(arred<-0.000001||arred>0.000001) {
				erro = 1;
			}
			printf("%f\t",arred);
                }
        }
	hfunit_assert(erro==0, msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}

void invert_test(char* msg) {
    	struct Matrix M1, M3, esperada;

        typ_var val1[16] = {val(1),val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16)};

	typ_var val3[16] = {val(0.25),val(0),val(-0.099),val(-0.19),val(-0.19),val(0),val(-0.09),val(0.3),val(0),val(-0.16),val(0.13),val(0.09),val(0),val(0.16),val(0.16),val(0)};

        M1 = set_values(4, 4, val1);
        esperada = set_values(4, 4, val3);
        M3 = Invert(M1);
        int erro = 0;
    	for (int i=0; i<4; i++) {
        	for(int j=0; j<4; j++) {
			float arred = get_value(M3,i,j)-get_value(esperada,i,j);
			if(arred<-0.000001||arred>0.000001){
				erro = 1;
			}
           	}
        }
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}

void zeros_test(char* msg) {
	struct Matrix M3, esperada;

        typ_var val3[16] = {val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0)};

        esperada = set_values(4, 4, val3);
        M3 = zeros(4, 4);
        int erro = 0;

        for (int i=0; i<4; i++) {
                for(int j=0; j<4; j++) {
			if(get_value(M3,i,j)!=get_value(esperada,i,j)) {
				erro = 1;
                	}
        	}
	}
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}


void setEye_test(char* msg) {
	struct Matrix M3, esperada;

        typ_var val3[16] = {val(1),val(0),val(0),val(0),val(0),val(1),val(0),val(0),val(0),val(0),val(1),val(0),val(0),val(0),val(0),val(1)};

        esperada = set_values(4, 4, val3);
        M3 = setEye(4);
        int erro = 0;

        for (int i=0; i<4; i++) {
            for(int j=0; j<4; j++) {
		if (get_value(M3,i,j)!=get_value(esperada,i,j)) {
			erro = 1;
		} 
            }
        }
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}

void ones_test(char* msg) {
	struct Matrix M3, esperada;

        typ_var val3[16] = {val(1),val(1),val(1),val(1),val(1),val(1),val(1),val(1),val(1),val(1),val(1),val(1),val(1),val(1),val(1),val(1)};

        esperada = set_values(4, 4, val3);
        M3 = ones(4, 4);
        int erro = 0;

        for (int i=0; i<4; i++) { 
                for(int j=0; j<4; j++) {
			if(get_value(M3,i,j)!=get_value(esperada,i,j)) {
                        	erro = 1;
			}
                }
        }
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}

void blkdiag2_test(char* msg) {
	struct Matrix M1, M2, M3, esperada;
        typ_var val1[16] = {val(1),val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16)};

        typ_var val2[16] = {val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16),val(17)};

        typ_var val3[64] = {val(1),val(2),val(3),val(4),val(0),val(0),val(0),val(0),val(5),val(6),val(7),val(8),val(0),val(0),val(0),val(0),val(9),val(10),val(11),val(12),val(0),val(0),val(0),val(0),val(13),val(14),val(15),val(16),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(0),val(2),val(3),val(4),val(5),val(0),val(0),val(0),val(0),val(6),val(7),val(8),val(9),val(0),val(0),val(0),val(0),val(10),val(11),val(12),val(13),val(0),val(0),val(0),val(0),val(14),val(15),val(16),val(17)};
        M1 = set_values(4, 4, val1);
        M2 = set_values(4, 4, val2);
        esperada = set_values(8, 8, val3);
        M3 = blkdiag2(M1, M2);
        int erro = 0;
	
	for (int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			if(get_value(M3,i,j)!=get_value(esperada,i,j)) {
				erro = 1;
			}
		}
	}
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M3);
        printf("Esperada:\n");
        print_matrix(esperada);
}

void customMat_test(char* msg) {
	struct Matrix M1, M2, M3, M5, M7, esperada;
	int conf[4] = {2,2,8,8};

	typ_var val1[16] = {val(1),val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16)};

        typ_var val2[16] = {val(2),val(3),val(4),val(5),val(6),val(7),val(8),val(9),val(10),val(11),val(12),val(13),val(14),val(15),val(16),val(17)};

	typ_var val3[16] = {val(4),val(2),val(2),val(2),val(0),val(1),val(-3),val(3),val(0),val(-1),val(3),val(3),val(0),val(3),val(1),val(1)};

	typ_var val4[64] = {val(1),val(2),val(3),val(4),val(2),val(3),val(4),val(5),val(5),val(6),val(7),val(8),val(6),val(7),val(8),val(9),val(9),val(10),val(11),val(12),val(10),val(11),val(12),val(13),val(13),val(14),val(15),val(16),val(14),val(15),val(16),val(17),val(4),val(2),val(2),val(2),val(3),val(5),val(7),val(9),val(0),val(1),val(-3),val(3),val(11),val(13),val(15),val(17),val(0),val(-1),val(3),val(3),val(19),val(21),val(23),val(25),val(0),val(3),val(1),val(1),val(27),val(29),val(31),val(33)};

	M1 = set_values(4, 4, val1);
        M2 = set_values(4, 4, val2);
	M3 = set_values(4, 4, val3);
	M5 = sum(M1, M2);
	M7 = customMat(conf, 4, M1, M2, M3, M5);
	esperada = set_values(8,8,val4);
	int erro = 0;
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			if(get_value(M7,i,j)!=get_value(esperada,i,j)) {
				erro = 1;
			}
		}
	}
	hfunit_assert(erro==0,msg);
	printf("Resultado:\n");
        print_matrix(M7);
        printf("Esperada:\n");
        print_matrix(esperada);	
}

void mat_test() {
	transposed_test ("Matriz transposta");
	sum_matrix_test("Soma de duas matrizes");
	subtract_matrix_test("Subtração de matrizes");
	mult_matrix_test("Multiplicação de matrizes");
	multE_test("Multiplicação de matriz por um número");
	divE_test("Divisão de uma matriz por um número");
	zeros_test("Matriz nula");
	setEye_test("Matriz identidade");
	ones_test("Matriz de 1");
	blkdiag2_test("Concatenação diagonal de duas matrizes");
	customMat_test("Matriz customizada");
}

//main test
void hfunit_test() {
	mat_test();
}
