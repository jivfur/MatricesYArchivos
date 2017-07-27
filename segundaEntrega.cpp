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


void guardarMatriz(char *fileName, int **matriz) {
	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}
	char linea[80];
	sprintf(linea, "%d %d\n", filas, cols);
	fputs(linea, fp);
	for (int i = 0; i < filas; i++) {
		linea[0] = '\0';
		for (int j = 0; j < cols; j++) {
			char buffer[10];
			sprintf(buffer, "%d ", matriz[i][j]);
			strcat(linea, buffer);
		}
		int len = strlen(linea);
		linea[len - 1] = '\n';
		fputs(linea, fp);
	}
	fclose(fp);

}



int main() {
	int **M = llenarMatriz(10, 5);
	imprimeMatriz(M);
	guardarMatriz("output.txt", M);
	int **M2 = leerMatriz("output.txt");
	printf("LO QUE SE LEE DEL ARCHIVO: \n");
	imprimeMatriz(M2);
	system("pause");
	return EXIT_SUCCESS;
}
