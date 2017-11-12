/*
author: jivfur
date:11/12/2017
Descripcion:
V1: Definicion de la estructura, Inicialización
V2: Producto de Dos Matrices
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	double **datos;
	int fil;
	int col;
}Matrix;

Matrix inicializa(int filas, int cols) {
	Matrix M;
	M.fil = filas;
	M.col = cols;
	M.datos = new (double*[filas]);
	for (int i = 0; i < filas; i++) {
		M.datos[i] = new (double[cols]);
		for (int j = 0; j < cols; j++) {
			M.datos[i][j] = 0.0;
		}
	}
	return M;
}

Matrix inicializaRandom(int filas, int cols) {
	Matrix M;
	M.fil = filas;
	M.col = cols;
	M.datos = new (double*[filas]);
	for (int i = 0; i < filas; i++) {
		M.datos[i] = new (double[cols]);
		for (int j = 0; j < cols; j++) {
			M.datos[i][j] = rand()%10;
		}
	}
	return M;
}

void printMatrix(Matrix M) {
	for (int i = 0; i < M.fil; i++) {
		for (int j = 0; j < M.col; j++) {
			printf("%0.2f\t", M.datos[i][j]);
		}
		printf("\n");
	}
}

Matrix producto(Matrix A, Matrix B) {
	Matrix C = inicializa(A.fil,B.col);
	if (A.col == B.fil) {
		for (int i = 0; i < A.fil; i++) {
			for (int j = 0; j < A.col; j++) {
				for (int k = 0; k < B.col; k++) {
					C.datos[i][k] += A.datos[i][j] * B.datos[j][k];
				}
			}
		}
	}
	else {
		printf("Error: Las Matrices no tienen la dimension requerida\n");
		C.fil = -1;
		C.col = -1;
		free(C.datos);
	}
	return C;
}


int main() {
	Matrix A = inicializaRandom(3, 4);
	Matrix B = inicializaRandom(4, 3);
	Matrix C = producto(A, B);
	printMatrix(A);
	printf("\n");
	printMatrix(B);
	printf("\n");
	printMatrix(C);
	system("pause");
	return 1;
}