//
//  main.cpp
//  Problem_8
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
#include <math.h>
#define La 0.14159265

double A=0.5;
double my_f(double x, double y){
    double a,b,c;
    a=A*(1+y+pow(x,2)+pow(x,3));
    b=x+sqrt(x)+La;
    c=a/b;
    return c;
}
double getvar(char a){
    double var;
    printf("input %c->",a);
    scanf("%lf",&var);
    return var;
}
void wait(){
    printf("\n press 0 to quit\n");
    int c;
    scanf("%d",&c);
}
    
int main(int argc, const char * argv[]) {
    double x,y,f;
    x=getvar('x');
    y=getvar('y');
    f=my_f(x,y);
    printf("x=%lf, y=%lf, f(x,y)=%lf\n",x,y,f);
    wait();
}
