/*
author: jivfur
date: 2017/07/26
description: Generacion de Matrices de manera aleatoria
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int filas = 0;
int cols = 0;

int** llenarMatriz(int f, int c) {
	filas = f;
	cols = c;
	int **matriz = new int*[f];	
	for (int i = 0; i < f; i++) {
		matriz[i] = new int[c];
		for (int j = 0; j < c; j++) {
			matriz[i][j] = rand() % 100;
		}
	}
	return matriz;
}

void imprimeMatriz(int **matriz) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d\t", matriz[i][j]);
		}
		printf("\n");
	}
}

int main() {
	int **M = llenarMatriz(10, 5);
	imprimeMatriz(M);
	system("pause");
	return EXIT_SUCCESS;
}
