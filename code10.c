#include <stdio.h>
#include <stdlib.h>
#include <math.h>
float** computeH(float *v, int rows) {
  float **h = (float**)malloc(rows*sizeof(float*));
  int i;
  for (i = 0 ; i < rows ; i++) {
    int j;
    h[i] = (float*)malloc(rows*sizeof(float));
    for (j = 0 ; j < rows ; j++) {
      h[i][j] = (i==j)?1:0;
      h[i][j] -= 2*v[i]*v[j];
    }
  }
  return h;
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

float** computeHBH(float **h, float **b, int rows){
  float **ans0 = multiply(h, rows, rows, b, rows, rows);
  float **ans = multiply(ans0, rows, rows, h, rows, rows);
  int i;
  for (i = 0 ; i < rows ; i++) {
    free(ans0[i]);
  }
  free(ans0);
  return ans;
}
void main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("user ./a.out file_A\n");
    return;
  }
  FILE *fp = fopen(argv[1], "r");
  int rows, cols;
  fscanf(fp, "%d %d", &rows, &cols);
  if (rows != cols) {
    printf("Please enter sym matrix\n");
    return;
  }
  float **mat = (float**)malloc(rows*sizeof(float*));
  int i;
  for (i = 0 ; i < rows ; i++){
    int j;
    mat[i] = (float*)malloc(cols*sizeof(float));
    for (j = 0 ; j < cols ; j++) {
      fscanf(fp, "%f", &mat[i][j]);
    }
  }
  fclose(fp);
  int k = 0;
  float **b = mat;
  while(k < rows - 2) {
    float s = 0;
    for (i = k+1 ; i < rows ; i++) {
      s += (b[i][k])*(b[i][k]);
    }
    s = sqrt(s);
    if (s == 0) {
      k += 1;
      continue;
    }
    int sg = b[k+1][k] < 0 ? -1 : 1;
    float z = 0.5*(1+sg*b[k+1][k]/s);
    float *v = (float*)malloc(rows*sizeof(float));
    for (i=0; i <= k ; i++) {
      v[i] = 0;
    }
    v[k+1] = sqrt(z);
    for (i = k+2 ; i < rows ; i++) {
      v[i] = sg*b[k][i]/(2*v[k+1]*s);
    }
    float **h = computeH(v, rows);
    float **tmpb = b;
    b = computeHBH(h, b, rows);
    for (i = 0 ; i < rows ; i++) {
      free(h[i]);
      free(tmpb[i]);
    }
    free(h);
    free(tmpb);
    free(v);
    k += 1;
  }
  for (i = 0 ; i < rows ; i++) {
    int j = 0 ; 
    for (j = 0 ; j < cols ; j++) {
      printf("%f\t",b[i][j]);
    }
    printf("\n");
  }
}
