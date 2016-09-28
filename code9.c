#include<stdio.h>
#include<stdlib.h>
float* multiply(float** mat, float* x, int rows, int cols) {
  float* y = (float*)malloc(rows*sizeof(float));
  int i ;
  for(i = 0 ; i < rows ; i++){
    int j = 0;
    y[i] = 0;
    for(j = 0 ; j < rows; j++) {
      y[i] += mat[i][j]*x[j];
    }
  }
  return y;
}
int getMaxElemInd(float* x, int rows){
  float maxElem = x[0];
  int maxInd = 0;
  int i;
  for(i = 0 ; i < rows ; i++){
    if (maxElem < x[i]){
      maxElem = x[i];
      maxInd = i;
    }
  }
  return maxInd;
}
float computeEigenValue(float** mat, int rows, int cols){
  int i;
  float* x = (float*)malloc(rows*sizeof(float));
  for (i = 0 ; i < rows ; i++){
    x[i] = 1;
  }
  float error = 1;
  float eigenValue = 1;
  while(error >= 1E-10) {
     float oldEigenValue = eigenValue;
     float* y = multiply(mat, x, rows, cols);
     int maxInd = getMaxElemInd(x, rows);
     eigenValue = y[maxInd]/x[maxInd];
     if (eigenValue >= 10E+38 || eigenValue <= -10E+39){
       return oldEigenValue;
     }
     free(x);
     x = y;
     error = (oldEigenValue-eigenValue)*(oldEigenValue-eigenValue);
     printf("E %f, Er %f\n", eigenValue, error);
  }
  free(x);
  return eigenValue;
}
void main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("use ./a.out matrixfile\n");
    return;
  }
  FILE* fp = fopen(argv[1], "r");
  int rows, cols;
  fscanf(fp, "%d %d", &rows, &cols);
  float** mat = (float**)malloc(rows*sizeof(float*));
  int i;
  for (i = 0 ; i < rows ; i++){
    mat[i] = (float*)malloc(cols*sizeof(float));
    int j;
    for (j = 0 ; j < cols; j++){
      fscanf(fp, "%f", &mat[i][j]);
    }
  }
  fclose(fp);
  float eigenValue = computeEigenValue(mat, rows, cols);
  printf("Largest eigen value %f\n", eigenValue);
  for (i = 0 ; i < rows ; i++){
    mat[i][i] = mat[i][i]-eigenValue;
  }
  printf("Smallest eigen value %f\n", computeEigenValue(mat, rows, cols));
}
