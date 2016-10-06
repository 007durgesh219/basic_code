#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define abs(a) (a)>=0?(a):(-(a))
void main() {
    int degree;
    printf("Enter degree of polynomial: ");
    scanf("%d", &degree);
    if (degree < 4) {
	printf("Degree should be >= 4\n");
	return;
    }
    int i;
    float coff[degree+1];
    for (i = 0 ; i <= degree ; i++) {
	printf("Enter %dth coff: ", i);
	scanf("%f", &coff[i]);
    }
    printf("Polynomial is: ");
    for (i = 0 ; i <= degree ; i++) {
	if (i == 0) {
	    printf("%.2f ", coff[i]);
	}else {
	    printf(" + %.2fx^%d", coff[i],i);
	}
    }
    printf("\n");
    float r,s;
    //printf("Enter initial values of u and v: ");
    //scanf("%f %f",&r,&s);
    r = coff[degree-1]/coff[degree];
    s = coff[degree-2]/coff[degree];
    float coffb[degree+1], coffc[degree+1];
    float err = 1;
    float delr, dels;
    int itr = 1;
    while(err > 10e-4) {
	coffb[degree] = coff[degree];
	coffb[degree-1] = coff[degree-1]+r*coffb[degree];
	for (i = degree-2 ; i >= 0 ; i--) {
	    coffb[i] = coff[i]+r*coffb[i+1]+s*coffb[i+2];
	}
	coffc[degree] = coffb[degree];
	coffc[degree-1] = coffb[degree-1] + r*coffc[degree];
	for (i = degree-2 ; i >= 0 ; i--) {
	    coffc[i] = coffb[i] + r*coffc[i+1] + s*coffc[i+2];
	}
	if (coffc[3] != 0){
	    delr = (-coffb[0]+coffb[1]*coffc[2]/coffc[3])/(coffc[1]-coffc[2]*coffc[2]/coffc[3]);
	    dels = (-coffb[1]-coffc[2]*delr)/coffc[3];
	} else if(coffc[3] == 0 && coffc[2] != 0){
	    delr = -coffb[1]/coffc[2];
	    dels = (-coffb[0]-coffc[1]*delr)/coffc[2];
	} else {
	    dels = 0;
	    s = 0;
	    delr = coffb[0]/coffc[1];
	}
	err = abs(delr/r)*100*abs(dels/s)*100;
	r = r+delr;
	s = s+dels;
	printf("Itr=%d\n",itr);
	for (i = degree ; i >= 0 ; i--) {
	    printf("b[%d]=%.2f ",i,coffb[i]);
	}
	printf("\n");
        for (i = degree ; i >= 0 ; i--) {
	    printf("c[%d]=%.2f ",i,coffc[i]);
	}
	printf("\n");
	printf("u=%.2f & v=%.2f\n",r,s);
	itr++;
    }
    printf("Roots are:\n");
    if (r*r+4*s < 0) {
	printf("[1.] %.2f+i%.2f,",r/2,sqrt(-(r*r+4*s))/2);
	printf("[2.] %.2f-i%.2f,",r/2,sqrt(-(r*r+4*s))/2);
    } else {
	printf("[1.] %.2f,",(r+sqrt(r*r+4*s))/2);
	printf("[2.] %.2f,",(r-sqrt(r*r+4*s))/2);
    }
    if (coffb[3]*coffb[3]-4*coffb[4]*coffb[2] < 0) {
        printf("[3.] %.2f+i%.2f,",-coffb[3]/(2*coffb[4]),sqrt(-(coffb[3]*coffb[3]-4*coffb[4]*coffb[2]))/(2*coffb[4]));
        printf("[4.] %.2f-i%.2f\n",-coffb[3]/(2*coffb[4]),sqrt(-(coffb[3]*coffb[3]-4*coffb[4]*coffb[2]))/(2*coffb[4]));
    } else {
        printf("[3.] %.2f",-coffb[3]/(2*coffb[4])+sqrt((coffb[3]*coffb[3]-4*coffb[4]*coffb[2]))/(2*coffb[4]));
        printf("[4.] %.2f\n",-coffb[3]/(2*coffb[4])-sqrt((coffb[3]*coffb[3]-4*coffb[4]*coffb[2]))/(2*coffb[4]));

    }
}
