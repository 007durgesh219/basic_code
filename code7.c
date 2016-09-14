#include <stdio.h>
#include <stdlib.h>
#define mod(a) a>=0?a:(-a)
// return row for which elemnt in pcol is max
int maxRowElem(float** mat, int rows, int pcol){
  int i, maxrow=0;
  float max = mat[maxrow][pcol]; 
  for(i = pcol ; i < rows ; i++) {
    if(max < mod(mat[i][pcol])) {
      maxrow = i ; 
      max = mod(mat[i][maxrow]);
    }
  }
  return maxrow;
}
void swap(float** mat, int fromrow, int torow) {
  float* row = mat[fromrow];
  mat[fromrow] = mat[torow];
  mat[torow] = row;
}
float** multiply(float** mat1, int rows1, int cols1, float** mat2, int rows2, int cols2) {
  float** mult = (float**)malloc(rows1*sizeof(float*));
  int i;
  for(i = 0; i<rows1; i++){
    mult[i] = (float*)malloc(cols2*sizeof(float));
    int j = 0;
    for(j = 0 ; j < cols2 ; j++) {
      mult[i][j] = 0;
      int k;
      for(k = 0 ; k < rows2 ; k++) {
	mult[i][j] += mat1[i][k]*mat2[k][j];
      }
    }
  }
  return mult;
}
int gussElem(float** mat, int rows, int cols, float** P) {
  int i,j,k;
  int sign = 1;
  for(i = 0 ; i < rows-1 ; i++) {
    int maxrow = maxRowElem(mat, rows, i);
    if (maxrow != i) {
      swap(mat, maxrow, i);
      swap(P, maxrow, i);
      sign = -1*sign;
    }
    if(mat[i][i] == 0)
      return 0;
    for(j = i+1; j < rows ; j++) {
      double value = mat[j][i]/mat[i][i];
      for(k = i ; k < cols ; k++) {
	mat[j][k] = mat[j][k]-mat[i][k]*value;
      }
    }
  }
  return sign;
}
float* UbackSubstitution(float** mat, int rows, int cols, float* b) {
  float* ans = (float*)malloc(rows*sizeof(float));
  int i;
  for (i = rows-1 ; i >= 0 ; i--) {
    float val = b[i];
    int j = 0;
    for (j = 0 ; j < rows-1-i ; j++) {
      val -= (mat[i][i+j+1]*ans[i+j+1]);
    }
    ans[i] = val/mat[i][cols-1-(rows-1-i)];
  }
  return ans;
}
float* LbackSubstitution(float** mat, int rows, int cols, float* b) {
  float* ans = (float*)malloc(rows*sizeof(float));
  int i;
  for(i = 0 ; i < rows ; i++) {
    float val = b[i];
    int j = 0;
    for (j = 0 ; j < i ; j++) {
      val -= (mat[i][j]*ans[j]);
    }
    ans[i] = val/mat[i][i];
  }
  return ans;
}
void main(int argc, char** argv) {
  if (argc < 3) {
    printf("Please use ./a.out file_A file_b\n");
    return;
  }
  FILE* fp = fopen(argv[1], "r");
  int rows, cols;
  fscanf(fp, "%d %d", &rows, &cols);
  if (rows < cols) {
    printf("Number of equations should be more then or equal to variables\n");
    return;
  }
  float** mat = (float**)malloc(rows*sizeof(float*));
  float** L = (float**)malloc(rows*sizeof(float*));
  float** U = (float**)malloc(rows*sizeof(float*));
  float** P = (float**)malloc(rows*sizeof(float*));
  int i = 0;
  for(i = 0 ; i < rows ; i++) {
    mat[i] = (float*)malloc(cols*sizeof(float));
    L[i] = (float*)malloc(cols*sizeof(float));
    U[i] = (float*)malloc(cols*sizeof(float));
    P[i] = (float*)malloc(cols*sizeof(float));
    int j = 0;
    for(j = 0 ; j < cols ; j++) {
      fscanf(fp, "%f", &mat[i][j]);
      U[i][j] = mat[i][j];
      L[i][j] = (i==j);
      P[i][j] = (i==j);
    }
  }
  fclose(fp);
  fp = fopen(argv[2], "r");
  int dummy;
  fscanf(fp, "%d %d", &dummy, &dummy);
  float* b = (float*)malloc(rows*sizeof(float));
  for (i = 0 ; i < rows ; i++) {
    fscanf(fp, "%f", &b[i]);
  }
  int sign = gussElem(U, rows, cols, P);
  float** mult = multiply(P, rows, cols, mat, rows, cols);
  float** bmult0 = (float**)malloc(rows*sizeof(float*));
  for (i = 0 ; i < rows ; i++) {
    bmult0[i] = (float*)malloc(sizeof(float));
    bmult0[i][0] = b[i];
  }
  bmult0 = multiply(P, rows, cols, bmult0, rows, 1);
  float* bmult = (float*)malloc(rows*sizeof(float));
  for (i = 0 ; i < rows ; i++) {
    bmult[i] = bmult0[i][0];
    printf("%f\n", bmult[i]);
  }
  if (!sign) {
    printf("Can't do gauss elimination\n'");
    return;
  }
  printf("PA:\n");
  for (i = 0 ; i < rows ; i++) {
    int j;
    for(j = 0 ; j < cols ; j++) {
      printf("%f\t", mult[i][j]);
    }
    printf("\n");
  }

  for (i = 0 ; i < rows ; i++) {
    int j = 0 ;
    for(j = 0 ; j < i ; j++) {
      L[i][j] = mult[i][j];
      int k = 0;
      for(k = 0 ; k < j ; k++) {
	L[i][j] -= L[i][k]*U[k][j];
      }
      L[i][j] /= U[j][j];
    }
  }
  printf("U:\n");
  for (i = 0 ; i < rows ; i++) {
    int j;
    for(j = 0 ; j < cols ; j++) {
      printf("%f\t", U[i][j]);
    }
    printf("\n");
  }
  printf("L:\n");
  for (i = 0 ; i < rows ; i++) {
    int j;
    for(j = 0 ; j < cols ; j++) {
      printf("%f\t", L[i][j]);
    }
    printf("\n");
  }
  float* b1 = LbackSubstitution(L, rows, cols, bmult);
  printf("b:\n");
  for (i = 0 ; i < rows ; i++) {
    printf("%f\n", b1[i]);
  }
  float* ans = UbackSubstitution(U, rows, cols, b1);
  printf("Ans: \n");
  for(i = 0 ; i < rows ; i++) {
    printf("%f\n", ans[i]);
  }
}
