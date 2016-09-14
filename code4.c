#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define mod(a) a>=0?a:(-a)
// return row for which elemnt in pcol is max
int maxRowElem(double** mat, int rows, int pcol){
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
void swap(double** mat, int fromrow, int torow) {
  double* row = mat[fromrow];
  mat[fromrow] = mat[torow];
  mat[torow] = row;
}
int gussElem(double** mat, int rows, int cols, int usePoviting) {
  int i,j,k;
  int sign = 1;
  for(i = 0 ; i < rows-1 ; i++) {
    if(usePoviting == 1) {
      int maxrow = maxRowElem(mat, rows, i);
      if (maxrow != i) {
	swap(mat, maxrow, i);
	sign = -1*sign;
      }
    }
    if(mat[i][i] == 0)
      return usePoviting == 1?sign:0;
    for(j = i+1; j < rows ; j++) {
      double value = mat[j][i]/mat[i][i];
      for(k = i ; k < cols ; k++) {
        mat[j][k] = mat[j][k]-mat[i][k]*value;
      }
    }
  }
  return sign;
}
void main(int argc, char** argv) {
  if(argc <= 1) {
    printf("Please input a file as follows:\n ./a.out filename\n");
    return;
  }
  int rows, cols;
  FILE *fp;
  fp = fopen(argv[1], "r");
  //printf("enter num rows of matrix: ");
  fscanf(fp,"%d %d", &rows, &cols);
  if(rows != cols) {
    printf("Matrix needs to be squre\n");
    return;
  }
  //printf("enter num cols of matrix: ");
  //scanf("%d", &cols);
  double** mat = (double**)malloc(rows*sizeof(double*));
  int i = 0 ;
  for(; i<rows; i++) {
    //printf("Enter elements of %dth row of matrix: \n", i);
    mat[i] = (double*)malloc(cols*sizeof(double));
    int j = 0;
    for(; j<cols; j++){
      //printf("Enter element of %dth row and %dth column of matrix: ", i, j);
      fscanf(fp, "%f",&mat[i][j]);
    }
  }

/*  printf("Matrix is: \n");
  for(i = 0 ; i<rows;i++){
    int j = 0;
    for(j = 0 ; j < cols ; j++)
      printf("%f\t",mat[i][j]);
    printf("\n");
  }*/
  printf("Press 1 for without poviting and 2 for poviting\n");
  int usePoviting;
  clock_t begin = clock();
  scanf("%d", &usePoviting);
  usePoviting = usePoviting==1?0:1;
  int sign = gussElem(mat, rows, cols, usePoviting);
  if(sign == 0) {
    printf("Povit element is zero in Gauss Elimination, can't find determinant\n");
    return ;
  }
  double det = sign;
  for(i = 0 ; i < rows;  i++)
    det = det*mat[i][i];
  clock_t end = clock();
  double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
  printf("Determinant is: %f\n",det);
  printf("Time take: %f sec\n", time_spent);
}
