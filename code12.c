#include <stdio.h>
#include <stdlib.h>
float determinant(float a[4][4],float k)
{
  float s=1,det=0,b[4][4];
  int i,j,m,n,c;
  if (k==1)
  {
    return (a[0][0]);
  }
  else
  {
    det=0;
    for (c=0;c<k;c++)
    {
      m=0;
      n=0;
      for (i=0;i<k;i++)
      {
	for (j=0;j<k;j++)
	{
	  b[i][j]=0;
	  if (i != 0 && j != c)
	  {
	    b[m][n]=a[i][j];
	    if (n<(k-2))
	      n++;
	    else
	    {
	      n=0;
	      m++;
	    }
	  }
	}
      }
      det=det + s * (a[0][c] * determinant(b,k-1));
      s=-1 * s;
    }
  }

  return (det);
}
void transpose(float num[4][4],float fac[4][4],float r, float inverse[4][4])
{
  int i,j;
  float b[4][4],d;

  for (i=0;i<r;i++)
  {
    for (j=0;j<r;j++)
    {
      b[i][j]=fac[j][i];
    }
  }
  d=determinant(num,r);
  for (i=0;i<r;i++)
  {
    for (j=0;j<r;j++)
    {
      inverse[i][j]=b[i][j] / d;
    }
  }

}
void cofactor(float num[4][4],float f, float inverse[4][4])
{
  float b[4][4],fac[4][4];
  int p,q,m,n,i,j;

  for (q=0;q<f;q++)
  {
    for (p=0;p<f;p++)
    {
      m=0;
      n=0;
      for (i=0;i<f;i++)
      {
	for (j=0;j<f;j++)
	{
	  if (i != q && j != p)
	  {
	    b[m][n]=num[i][j];
	    if (n<(f-2))
	      n++;
	    else
	    {
	      n=0;
	      m++;
	    }
	  }
	}
      }
      fac[q][p]=pow(-1,q + p) * determinant(b,f-1);
    }
  }
  transpose(num,fac,f,inverse);
}
float k1=1.0,k2=0.2,k3=0.05,k4=0.4,theta=2,cao=1;
float F1(float ca, float cb, float cc, float cd) {
  return -ca+cao+theta*(-k1*ca-k2*sqrt(pow(ca,3))+k3*cc*cc);
}
float dF1a(float ca, float cb, float cc, float cd) {
  return -1+theta*(-k1-(3/2.0)*k2*sqrt(ca));
}
float dF1b(float ca, float cb, float cc, float cd) {
  return 0;
}
float dF1c(float ca, float cb, float cc, float cd) {
  return theta*2*k3*cc;
}
float dF1d(float ca, float cb, float cc, float cd) {
  return 0;
}
float F2(float ca, float cb, float cc, float cd) {
  return -cb+theta*(2*k1*ca-k4*cb*cb);
}
float dF2a(float ca, float cb, float cc, float cd) {
  return theta*2*k1;
}
float dF2b(float ca, float cb, float cc, float cd) {
  return -1-theta*2*k4*cb;
}
float dF2c(float ca, float cb, float cc, float cd) {
  return 0;
}
float dF2d(float ca, float cb, float cc, float cd) {
  return 0;
}
float F3(float ca, float cb, float cc, float cd) {
  return -cc+theta*(k2*sqrt(pow(ca,3))-k3*cc*cc+k4*cb*cb);
}
float dF3a(float ca, float cb, float cc, float cd) {
  return theta*3*k2*sqrt(ca)/2.0;
}
float dF3b(float ca, float cb, float cc, float cd) {
  return theta*k4*2*cb;
}
float dF3c(float ca, float cb, float cc, float cd) {
  return -theta*k3*2*cc;
}
float dF3d(float ca, float cb, float cc, float cd) {
  return 0;
}
float F4(float ca, float cb, float cc, float cd) {
  return -cd+theta*k4*cb*cb;
}
float dF4a(float ca, float cb, float cc, float cd) {
  return 0;
}
float dF4b(float ca, float cb, float cc, float cd) {
  return theta*k4*2*cb;
}
float dF4c(float ca, float cb, float cc, float cd) {
  return 0;
}
float dF4d(float ca, float cb, float cc, float cd) {
  return -1;
}
void J(float ca, float cb, float cc, float cd, float j[4][4]) {
  j[0][0] = dF1a(ca,cb,cc,cd);
  j[0][1] = dF1b(ca,cb,cc,cd);
  j[0][2] = dF1c(ca,cb,cc,cd);
  j[0][3] = dF1d(ca,cb,cc,cd);
  j[1][0] = dF2a(ca,cb,cc,cd);
  j[1][1] = dF2b(ca,cb,cc,cd);
  j[1][2] = dF2c(ca,cb,cc,cd);
  j[1][3] = dF2d(ca,cb,cc,cd);
  j[2][0] = dF3a(ca,cb,cc,cd);
  j[2][1] = dF3b(ca,cb,cc,cd);
  j[2][2] = dF3c(ca,cb,cc,cd);
  j[2][3] = dF3d(ca,cb,cc,cd);
  j[3][0] = dF4a(ca,cb,cc,cd);
  j[3][1] = dF4b(ca,cb,cc,cd);
  j[3][2] = dF4c(ca,cb,cc,cd);
  j[3][3] = dF4d(ca,cb,cc,cd);
}
void mult(float a[4][4], float b[4], float ans[4]) {
  int i;
  for (i = 0 ; i < 4; i++) {
    int j;
    for (j = 0 ; j < 1 ; j++) {
      ans[i] = 0;
      int k;
      for (k = 0 ; k < 4 ; k++) {
	ans[i] += a[i][k]*b[k];
      }
    }
  }
}
void main() {
  float k1=1.0,k2=0.2,k3=0.05,k4=0.4,theta=2,cao=1;
  //printf("Enter k1,k2,k3,k4,theta and Cao:");
  //scanf("%f %f %f %f %f %f",&k1,&k2,&k3,&k4,&theta,&cao);
  float j[4][4], invj[4][4],multiply[4],f[4];
  float ca=30,cb=40,cc=20,cd=50;
  float err = 1;
  int itr = 1,i;
  while(err > 10e-9) {
    J(ca,cb,cc,cd,j);
    cofactor(j,4,invj);
    f[0] = F1(ca,cb,cc,cd);
    f[1] = F2(ca,cb,cc,cd);
    f[2] = F3(ca,cb,cc,cd);
    f[3] = F4(ca,cb,cc,cd);
    mult(invj,f,multiply);
    err = 0;
    for (i = 0 ; i < 4 ; i++)
      err += multiply[i]*multiply[i];
    ca = ca-multiply[0];
    cb = cb-multiply[1];
    cc = cc-multiply[2];
    cd = cd-multiply[3];
    printf("itr=%d\n",itr);
    printf("ca=%0.2f,cb=%0.2f,cc=%0.2f,cd=%0.2f,err=%f\n",ca,cb,cc,cd,err);
    itr++;
  }
  printf("ca=%0.2f,cb=%0.2f,cc=%0.2f,cd=%0.2f\n",ca,cb,cc,cd);
}
