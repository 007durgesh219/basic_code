#include <stdio.h>
#include <stdlib.h>
#define mod(a) a>=0?a:(-a)
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
int gussElem(float** mat, int rows, int cols) {
  int i,j,k;
  int sign = 1;
  for(i = 0 ; i < rows-1 ; i++) {
    /*int maxrow = maxRowElem(mat, rows, i);
    if (maxrow != i) {
      swap(mat, maxrow, i);
      sign = -1*sign;
    }*/
    if(mat[i][i] == 0)
      return 0;
    for(j = i+1; j < rows ; j++) {
      float value = mat[j][i]/mat[i][i];
      for(k = i ; k < cols+1 ; k++) {
	mat[j][k] = mat[j][k]-mat[i][k]*value;
      }
    }
  }
  return sign;
}
float* backSubstitution(float** mat, int rows, int cols) {
  float* ans = (float*)malloc(rows*sizeof(float));
  int i;
  for (i = rows-1 ; i >= 0 ; i--) {
    float val = mat[i][cols];
    int j = 0;
    for (j = 0 ; j < rows-1-i ; j++) {
      val -= (mat[i][i+j+1]*ans[(int)mat[i+j+1][cols+1]]);
    }
    ans[(int)mat[i][cols+1]] = val/mat[i][cols-1-(rows-1-i)];
  }
  return ans;
}
void main(int argc, char** argv) {
  if(argc <= 2) {
    printf("Please input a file as follows:\n ./a.out A_file b_file\n");
    return;
  }
  int rows, cols;
  FILE *fp;
  fp = fopen(argv[1], "r");
  fscanf(fp, "%d %d", &rows, &cols);
  if(rows < cols) {
    printf("Number of equations should be more then or equal to number of variables\n");
    return;
  }
  float** mat = (float**)malloc((rows)*sizeof(float*));
  int i = 0;
  for (i = 0 ; i < rows ; i++) {
    mat[i] = (float*)malloc((cols+2)*sizeof(float));
    int j = 0;
    for (j = 0 ; j < cols ; j++) {
      fscanf(fp, "%f", &mat[i][j]);
    }
  }
  fclose(fp);
  fp = fopen(argv[2], "r");
  int dummy;
  fscanf(fp, "%d %d", &dummy, &dummy);
  for (i = 0 ; i < rows ; i++) {
    fscanf(fp, "%f", &mat[i][cols]);
    mat[i][cols+1] = i;
  }
  int sign = gussElem(mat, rows, cols);
  if (!sign) {
    printf("Cannot solve equation\n");
    return;
  }
  for (i = 0 ; i < rows ; i++){
      int j;
      for (j = 0 ; j < cols+1 ; j++){
	  //printf("%f\t", mat[i][j]);
      }
      //printf("\n");
  }
  float* ans = backSubstitution(mat, rows, cols);
  for (i = 0 ; i < rows ; i++) {
    printf("%f\n", ans[i]);
  }
}
