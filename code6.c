#include <stdio.h>
#include <stdlib.h>
#define mod(a) a>=0?a:(-a)
int findNonZero(float** mat, int rows, int pcol){
  int i;
  for(i = pcol ; i < rows ; i++) {
    if(mat[i][pcol] != 0) {
      return i;
    }
  }
  return -1;
}
void swap(float** mat, int fromrow, int torow) {
  float* row = mat[fromrow];
  mat[fromrow] = mat[torow];
  mat[torow] = row;
}
int gussElem(float** mat, int rows, int cols) {
  int i,j,k;
  int sign = 1;
  for(i = 0 ; i < rows ; i++) {
    if (mat[i][i] == 0) {
      int nonZeroRow = findNonZero(mat, rows, i);
      if (nonZeroRow == -1) {
	return 0;
      }
      swap(mat, nonZeroRow, i);
      sign = -1*sign;
    }
    if(mat[i][i] == 0)
      return 0;
    float value = mat[i][i];
    for (j = 0 ; j < 2*cols+1 ; j++) {
      mat[i][j] /= value;
    }
    for(j = 0; j < rows ; j++) {
      if (j == i)
	continue;
      float value = mat[j][i];
      for(k = 0 ; k < 2*cols+1 ; k++) {
	mat[j][k] = mat[j][k]-mat[i][k]*value;
      }
    }
  }
  return sign;
}

void main(int argc, char** argv) {
  if (argc <= 2) {
    printf("Please input a file as follows:\n ./a.out A_file b_file\n");
    return;
  }
  int rows, cols;
  FILE *fp;
  fp = fopen(argv[1], "r");
  fscanf(fp, "%d %d", &rows, &cols);
  if (rows < cols) {
    printf("Number of equations should be more then or equal to number of variables\n");
    return;
  }
  float** mat = (float**)malloc(rows*sizeof(float*));
  int i = 0;
  for (i = 0 ; i < rows ; i++){
    int j = 0;
    mat[i] = (float*)malloc((2*cols+2)*sizeof(float));
    for (j = 0 ; j < cols ; j++) {
      fscanf(fp, "%f", &mat[i][j]);
      mat[i][cols+j+1] = (i==j);
    }
  }
  fclose(fp);
  fp = fopen(argv[2], "r");
  int dummy;
  fscanf(fp, "%d %d", &dummy, &dummy);
  for (i = 0 ; i < rows ; i++) {
    fscanf(fp,"%f", &mat[i][cols]);
    mat[i][2*cols+1] = i;
  }
  int sign = gussElem(mat, rows, cols);
  float *ans = (float*)malloc(rows*sizeof(float));
  for (i = 0 ; i < rows ; i++) {
    int j = 0;
    //printf("%f\n", mat[i][2*cols+1]);
    ans[(int)mat[i][2*cols+1]] = mat[i][cols];
    /*for (j = cols+1 ; j < 2*cols+1 ; j++) {
      printf("%f\t", mat[i][j]);
    }
    printf("\n");*/
  }
  for(i = 0 ; i < rows ; i++) {
    printf("%f\n",ans[i]);
  }
}
