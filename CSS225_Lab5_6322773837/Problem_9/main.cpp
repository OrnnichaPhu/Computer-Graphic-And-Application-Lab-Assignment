//
//  main.cpp
//  Problem_9
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
#include <math.h>
#define Al 7.89161
double A=0.5;
double my_f(double x, double y, double z){
    double a;
    a=A*(sqrt(fabs(tan(Al*x)+10*atan(z*y))));
    return a;
}
double getvar(char a){
    double var;
    printf("input %c->",a);
    scanf("%lf",&var);
    return var;
}
void calculate_fxyz(){
    double x,y,z,f;
    x=getvar('x');
    y=getvar('y');
    z=getvar('z');
    f=my_f(x,y,z);
    printf("x=%lf, y=%lf, z=%lf, f(x,y,z)=%lf\n",x,y,z,f);
}

void wait(){
    printf("\n press 0 to quit\n");
    int c;
    scanf("%d",&c);
}
    
int main(int argc, const char * argv[]) {
    calculate_fxyz();
    calculate_fxyz();
    calculate_fxyz();
    wait();
}

