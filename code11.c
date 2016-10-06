#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define R 82.05
float A, B;
float func(float z){
  return z*z*z - z*z + z*(A - B - B*B) - A*B;
}
float dfunc(float z){
  return 3*z*z - 2*z + (A-B-B*B);
}
float func1(float z) {
  return z*z*z+(B-1)*z*z+(A-3*B*B-2*B)*z-(A*B-B*B-B*B*B);
}
float dfunc1(float z) {
  return 3*z*z+2*(B-1)*z+(A-3*B*B-2*B);
}
float func2(float z){
  return z*z*z - (1+B)*z*z + A*z - A*B;
}
float dfunc2(float z) {
  return 3*z*z - (1+B)*2*z + A;
}
float findRoots(float (*f)(float), float (*df)(float), float x){
  float err = 1;
  while(err > 10E-9) {
    float newx = x - f(x)/df(x);
    err = (newx-x)*(newx-x);
    x = newx;
    //printf("%f %f\n", x, err);
  }
  return x;
}
void main(){
  float w=0.193, tc=425.2, pc=37.5, t, tr, pr;
  char ch;
  printf("Enter question [a,b,c or d]: ");
  scanf("%c", &ch);
  FILE *fp = fopen("pv.csv", "w");
  printf("Enter w: ");
  scanf("%f", &w);
  printf("Enter Tc: ");
  scanf("%f", &tc);
  printf("Enter Pc: ");
  scanf("%f", &pc);
  printf("Enter T: ");
  scanf("%f", &t);
  float p;
  for (p = 10.0 ; p < 100.0 ; p += 1.5) {
    pr = p/pc;
    tr = t/tc;
    float f;
    float (*ff)(float) = func;
    float (*df)(float) = dfunc;
    if (ch == 'a') {
      B = 0.08664*pr/tr;
      f = 1/tr*pow((1+(0.48+1.574*w-0.176*w*w)*(1-sqrt(tr))),2);
      A = 0.42748*pr*f/tr;
    } else if (ch == 'b') {
      B = 0.08664*pr/tr;
      f = 1/sqrt(t*t*t);
      A = 0.42748*pr*f/tr;
    } else if (ch == 'c') {
      B = 0.07780*pr/tr;
      f = 1/tr*pow((1+(0.37464+1.54226*w-0.26922*w*w)*(1-sqrt(tr))),2);
      A = 0.45724*pr*f/tr;
      ff = func1;
      df = dfunc1;
    } else {
      B = 1/8*(pr/tr);
      A = 27/64*(pr/tr*tr);
      ff = func2;
      df = dfunc2;
    }
    float root = findRoots(ff, df, 0.05);
    //printf("%f\n", root);
    printf("%f, %f\n", p, root*R*t/p);
    fprintf(fp, "%f, %f\n", p, root*R*t/p);
    if (t < tc) {
      float root1 = findRoots(ff, df, 0.2);
      if (root1 != root) {
	printf("%f, %f\n", p, root1*R*t/p);
	fprintf(fp, "%f, %f\n", p, root1*R*t/p);
      }
      float root2 = findRoots(ff, df, 0.9);
      if (root1 != root && root1 != root2) {
	printf("%f, %f\n", p, root2*R*t/p);
	fprintf(fp,"%f, %f\n", p, root2*R*t/p);
      }
    }
  }
  fclose(fp);
}
