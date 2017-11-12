/*
author: jivfur
date:11/12/2017
Descripcion:
V1: Definicion de la estructura, Inicialización
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
			M.datos[i][j] = rand()%100;
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

int main() {
	Matrix M = inicializa(5,7);
	Matrix R = inicializaRandom(3, 4);
	printMatrix(M);
	printf("\n");
	printMatrix(R);
	printf("\n");
	system("pause");
	return 1;
}