#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** multiply_matrices(int**, int**, int, int, int, int);
void freeAll(int**, int, int);
void writeMatrix(FILE *fout, int **matrix, int m, int n);

double startTime, stopTime;

int main(int argc, char** argv) {

	FILE* fin;
	FILE* fout;

	/* open the file */
	fin = fopen(argv[1], "r");

	/* read the file */
	int m1 = 0;
	int n1 = 0;
	int m2 = 0;
	int n2 = 0;
	int i = 0;
	int j = 0;

	if(fscanf(fin, "%d %d", &m1, &n1) != 2) {
		printf("error\n");
		return 0;
	}

	int** array1 = (int**) malloc(m1 * sizeof(int*));

	for(i = 0; i < m1; i ++) {
		array1[i] = (int*) malloc(n1 * sizeof(int));
	}

	for(i = 0; i < m1; i ++) {
		for(j = 0; j < n1; j ++) {
			if(fscanf(fin, "%d", &array1[i][j]) != 1) {
				printf("error\n");
				return 0;
			}
			if(j == n1 - 1) {
				fscanf(fin, "\n");
			} else {
				fscanf(fin, " ");
			}
		}
	}

	fscanf(fin, "\n");

	if(fscanf(fin, "%d %d", &m2, &n2) != 2) {
		printf("error\n");
		return 0;
	}

	int** array2 = (int**) malloc(m2 * sizeof(int*));

	for(i = 0; i < m2; i ++) {
		array2[i] = (int*) malloc(n2 * sizeof(int));
	}

	for(i = 0; i < m2; i ++) {
		for(j = 0; j < n2; j ++) {
			if(fscanf(fin, "%d", &array2[i][j]) != 1) {
				printf("error\n");
				return 0;
			}
			if(j == n2 - 1) {
				fscanf(fin, "\n");
			} else {
				fscanf(fin, " ");
			}
		}
	}
	fclose(fin);

	/* add the matrices and print the result */
	if(m2 != n1) {
		printf("error\n");
		return 0;
	}

	startTime = clock();
	int** product = multiply_matrices(array1, array2, m1, n1, m2, n2);
	stopTime = clock();

	printf("%d * %d; SEQUENTIAL; %f secs\n", m1, n2, (stopTime-startTime)/CLOCKS_PER_SEC);

	fout = fopen("matrix_result.txt", "w");
	writeMatrix(fout, product, m1, n2);
	fclose(fout);

	freeAll(array1, m1, n1);
	freeAll(array2, m2, n2);
	freeAll(product, m1, n2);

	//print_matrix(product, m1, n2);
	return 0;
}

int** multiply_matrices(int** matrix1, int** matrix2, int m1, int n1, int m2, int n2) {
	if(n1 != m2) {
		printf("error\n");
		return NULL;
	}

	int i = 0;
	int j = 0;
	int k = 0;
	int** product = (int**) malloc(m1 * sizeof(int*));

	for(i = 0; i < m1; i ++) {
    product[i] = (int*) malloc(n2 * sizeof(int));
		for(j = 0; j < n2; j ++) {
      int r = matrix1[i][j];
			product[i][k] = 0;
			for(k = 0; k < n1; k ++) {
				product[i][k] += r * matrix2[j][k];
			}
		}
	}
  // ATTEMPT AT LOOP BLOCKING
  /*
    int i1 = m1-(3*(m1/4));
    int j1 = n2-(3*(n2/4));
    int k1 = n1-(3*(n1/4));

    int i2 = m1-(2*(m1/4));
    int j2 = n2-(2*(n2/4));
    int k2 = n1-(2*(n1/4));

    int i3 = m1-(m1/4);
    int j3 = n2-(n2/4);
    int k3 = n1-(n1/4);

    for(i = 0; i < i1; i++){
      block1[i] = (int*) malloc((n2/4) * sizeof(int));
      for(j = 0; j < j1; j++){
        int r = matrix1[i][j];
        for(k = 0; k < k1; k++){
          block1[i][k] += r * matrix2[j][k];
        }
      }
    }
    for(i1 = i; i1 < i2; i1++){
      block2[i1-i] = (int*) malloc(n2 * sizeof(int));
      for(j1 = 0; j1 < j2; j1++){
        int r = matrix1[i1][j1];
        for(k1 = k; k1 < k2; k1++){
          block2[i1-i][k1] += r * matrix2[j1][k1];
        }
      }
    }
    for(i2 = i1; i2 < i3; i2++){
      block3[i2-i1] = (int*) malloc(n2 * sizeof(int));
      for(j2 = j1; j2 < j3; j2++){
        int r = matrix1[i2][j2];
        for(k2 = k1; k2 < k3; k2++){
          block3[i2-i1][k2] += r * matrix2[j2][k2];
        }
      }
    }
    for(i3 = i2; i3 < m1; i3++){
      block4[i3-i2] = (int*) malloc(n2 * sizeof(int));
      for(j3 = j2; j3 < n2; j3++){
        int r = matrix1[i3][j3];
        for(k3 = k2; k3 < n1; k3++){
          block4[i3-i2][k3] += r * matrix2[j3][k3];
        }
      }
    }
  */
	return product;
}

/* Freeing fcts ------------------------------------------------------- */
void freeAll(int **matrix, int m, int n) {
	int i;
	for (i=0; i<m; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void writeMatrix(FILE *fout, int **matrix, int m, int n) {
	int i,j;

	for(i=0; i<m; i++) {
		for(j=0; j<n; j++)
			fprintf(fout,"%d ",matrix[i][j]);
		putc('\n',fout);
   }
}
