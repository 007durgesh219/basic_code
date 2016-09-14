#include <stdio.h>
#include <stdlib.h>
void main(int argc, char** argv) {
  int row1, col1, row2, col2;
  FILE *fp = fopen(argv[1], "r");
  printf("enter num rows of first matrix: ");
  fscanf(fp,"%d", &row1);
  printf("enter num cols of first matrix: ");
  fscanf(fp, "%d", &col1);
  float** mat1 = (float**)malloc(row1*sizeof(float*));
  int i = 0 ;
  for(; i<row1; i++) {
    printf("Enter elements of %dth row of first matrix: \n", i);
    mat1[i] = (float*)malloc(col1*sizeof(float));
    int j = 0;
    for(; j<col1; j++){
      printf("Enter element of %dth row and %dth column of first matrix: ", i, j);
      fscanf(fp, "%f",&mat1[i][j]);
    }
  }
  fclose(fp);
  fp = fopen(argv[2], "r");
  printf("enter num rows of second matrix: ");
  fscanf(fp, "%d", &row2);
  printf("enter num cols of second matrix: ");
  fscanf(fp, "%d", &col2);
  if (col1 != row2) {
      printf("%d %d %d %d\n", row1, col1, row2, col2);
    printf("Multiplication not possible due to dimension mismatch\n");
    return;
  }
  float** mat2 = (float**)malloc(row2*sizeof(float*));
  i = 0 ;
  for(; i<row2; i++) {
    printf("Enter elements of %dth row of second matrix: \n", i);
    mat2[i] = (float*)malloc(col2*sizeof(float));
    int j = 0;
    for(; j<col2; j++){
      printf("Enter element of %dth row and %dth column of second matrix: ", i, j);
      fscanf(fp, "%f",&mat2[i][j]);
    }
  }

  printf("First matrix is: \n");
  for(i = 0 ; i<row1;i++){
    int j = 0;
    for(j = 0 ; j < col1 ; j++)
      printf("%f\t",mat1[i][j]);
    printf("\n");
  }
  printf("Second matrix is: \n");
  for(i = 0 ; i<row2;i++){
    int j = 0;
    for(j = 0 ; j < col2 ; j++)
      printf("%f\t",mat2[i][j]);
    printf("\n");
  }

  
  float** mult = (float**)malloc(row1*sizeof(float*));
  for(i = 0; i<row1; i++){
    mult[i] = (float*)malloc(col2*sizeof(float));
    int j = 0;
    for(j = 0 ; j < col2 ; j++) {
      mult[i][j] = 0;
      int k;
      for(k = 0 ; k < row2 ; k++) {
        mult[i][j] += mat1[i][k]*mat2[k][j];
      }
    }
  }
  printf("Result matrix is: \n");
  for(i = 0 ; i<row1;i++){
    int j = 0;
    for(j = 0 ; j < col2 ; j++)
      printf("%f\t",mult[i][j]);
    printf("\n");
  }

}
