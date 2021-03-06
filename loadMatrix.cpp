/*
author: jivfur
date:11/12/2017
Descripcion:
V1: Definicion de la estructura, Inicialización
V2: Producto de Dos Matrices
V3: Inversa e Identidad
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


Matrix identidad(int filas, int cols) {
	Matrix M;
	M.fil = filas;
	M.col = cols;
	M.datos = new (double*[filas]);
	for (int i = 0; i < filas; i++) {
		M.datos[i] = new (double[cols]);
		for (int j = 0; j < cols; j++) {
			M.datos[i][j] = 0.0;
		}
		M.datos[i][i] = 1.0;
	}
	return M;
}

void switchRows(Matrix M, int r1, int r2) {
	float aux;
	for (int i = 0; i < M.col; i++) {
		aux = M.datos[r1][i];
		M.datos[r1][i] = M.datos[r2][i];
		M.datos[r2][i] = aux;
	}
}

void multiplyRowConstant(Matrix M, int r, float c) {
	for (int i = 0; i < M.col; i++) {
		M.datos[r][i] *= c;
	}
}

void addRows(Matrix M, int r1, int r2, float c) {
	for (int i = 0; i < M.col; i++) {
		M.datos[r1][i] += M.datos[r2][i] * c;
	}
}

Matrix clone(Matrix M) {
	Matrix N = inicializa(M.fil, M.col);
	for (int i = 0; i < M.fil; i++) {
		for (int j = 0; j < M.col; j++) {
			N.datos[i][j] = M.datos[i][j];
		}
	}
	return N;
}

Matrix gaussjordan(Matrix A) {
	Matrix M = clone(A);
	Matrix Inv = identidad(M.fil, M.col);
	if (M.fil == M.col) {
		for (int i = 0; i < M.fil; i++) {
			if (M.datos[i][i] == 0) {
				int r = 0;
				while (r < M.col && (M.datos[i][r] == 0 || M.datos[r][i] == 0)) {
					r++;
				}
				switchRows(M,i,r);
			}
			double c = 1.0 / M.datos[i][i];
			multiplyRowConstant(M, i, c);
			multiplyRowConstant(Inv, i, c);
			for (int j = 0; j < M.fil; j++) {
				if (i != j) {
					c = -M.datos[j][i];
					addRows(M, j, i, c);
					addRows(Inv, j, i, c);
				}
			}
		}
	}else {
		printf("Error La matriz no es cuadrada \n");
		Inv.fil = -1;
		Inv.col = -1;
		free(Inv.datos);
	}
	return Inv;
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

void saveMatrix(Matrix M, char* fileName) {
	FILE *fp;
	fopen_s(&fp, fileName, "w");
	char linea[80];
	/*
	INT INT
	FLOAT FLOAT ... FLOAT
	FLOAT FLOAT ... FLOAT
	:
	FLOAT FLOAT ... FLOAT
	*/
	if (fp != NULL) {
		sprintf_s(linea, "%d\t%d\n", M.fil, M.col);
		fputs(linea, fp);
		for (int i = 0; i < M.fil; i++) {
			for (int j = 0; j < M.col; j++) {
				sprintf_s(linea, "%.2f\t", M.datos[i][j]);
				fputs(linea, fp);
			}
			fputs("\n", fp);
		}
	}
	else {
		printf("No se pudo abrir el archivo %s\n", fileName);
	}
	fclose(fp);
}

Matrix loadMatrix(char* fileName) {
	Matrix M;
	FILE *fp;
	fopen_s(&fp,fileName,"r");
	char linea[80];
	char *nextToken;
	/*
	INT INT
	FLOAT FLOAT ... FLOAT
	FLOAT FLOAT ... FLOAT
	:
	FLOAT FLOAT ... FLOAT
	*/
	if (fp != NULL) {
		fgets(linea, 79, fp);
		char *ptr = strtok_s(linea,"\t",&nextToken);
		int f = atoi(ptr);
		int c = atoi(strtok_s(NULL, "\t", &nextToken));
		M = inicializa(f, c);
		f = 0;
		while (!feof(fp)) {
			fgets(linea, 79, fp);
			c = 0;
			ptr= strtok_s(linea, "\t", &nextToken);
			while (ptr != NULL && c < M.col && f < M.fil) {
				M.datos[f][c] = atof(ptr);
				c++;
				ptr = strtok_s(NULL, "\t\n", &nextToken);
			}
			f++;
		}


	}
	else {
		printf("Error al abrir el archivo %s\n", fileName);
		M = inicializa(-1, -1);
	}
	fclose(fp);

	return M;
}



int main() {
	Matrix A = loadMatrix(A,"A.txt");
	Matrix Inv = loadMatrix(Inv,"Inv.txt");
	Matrix C = loadMatrix(C,"C.txt");
	printMatrix(A);
	printf("\n");
	printMatrix(Inv);
	printf("\n");
	Matrix C = producto(A, Inv);
	printMatrix(C);

	system("pause");
	return 1;

}