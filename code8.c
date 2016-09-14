#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void init(float* x, int rows) {
  srand(time(NULL));
  int i;
  for(i = 0 ; i < rows ; i++) {
    x[i] = ((float)rand())/RAND_MAX;
    x[i] *= 0;
  }
}
float diff(float* x, float* y, int rows) {
  float ans = 0;
  int i;
  for(i = 0 ; i < rows ; i++) {
    ans += ((x[i]-y[i])*(x[i]-y[i]));
  }
  return sqrt(ans);
}
void main(int argc, char** argv) {
  if (argc < 3) {
    printf("use ./a.out file_A file_b\n");
    return;
  }
  FILE* fp = fopen(argv[1], "r");
  int rows, cols;
  fscanf(fp, "%d %d", &rows, &cols);
  float** mat = (float**)malloc(rows*sizeof(float*));
  int i;
  for(i = 0 ; i < rows ; i++) {
    mat[i] = (float*)malloc(cols*sizeof(float));
    int j;
    for(j = 0 ; j < cols ; j++) {
      fscanf(fp, "%f", &mat[i][j]);
    }
  }
  fclose(fp);
  fp = fopen(argv[2], "r");
  float* b = (float*)malloc(rows*sizeof(float));
  int dummy;
  fscanf(fp, "%d %d", &dummy, &dummy);
  for(i = 0 ; i < rows ; i++){
    fscanf(fp, "%f", &b[i]);
  }
  float* x = (float*)malloc(rows*sizeof(float));
  for (i = 0 ; i < rows ; i++) {
      int j = 0;
      for (j = 0 ; j < cols ; j++){
	  printf("%f\t", mat[i][j]);
      }
      printf("\n");
  }
  for (i = 0 ; i < rows ; i++) {
      printf("%f\t", b[i]);
  }
  printf("\n");
  init(x, rows);
  printf("Initial solution:\n");
  for (i = 0 ; i < rows ; i++) {
    printf("%f\n", x[i]);
  }
  float error = 1;
  int numit = 0;
  while(error >= 1e-8) {
    numit++;
    printf("%d:%f\n",numit, error);
    float* newx = (float*)malloc(rows*sizeof(float));
    for(i = 0 ; i < rows ; i++) {
      newx[i] = b[i];
      int j = 0;
      for (j = 0 ; j < rows ; j++) {
	if (j < i) {
	  newx[i] -= mat[i][j]*newx[j];
	} else if (j > i) {
	  newx[i] -= mat[i][j]*x[j];
	}
      }
      newx[i] /= mat[i][i];
      newx[i] = 0.2*x[i]+1.2*newx[i];
    }
    error = diff(newx, x, rows);
    free(x);
    x = newx;
  }
  printf("Ans:\n");
  for(i = 0 ; i < rows ; i++) {
      printf("%f\n", x[i]);
  }
}
