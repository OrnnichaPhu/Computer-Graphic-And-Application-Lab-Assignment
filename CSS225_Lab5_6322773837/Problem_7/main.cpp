//
//  main.cpp
//  Problem_7
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
#include <math.h>

double my_F(double x, double y){
    double a;
    a=1+(pow(sin(x),2)+pow(sin(2*x),2));
    a/=sqrt(cos(6*x)+pow(x, 3)-tan(y));
    return a;
}
double getx(){
    double x;
    printf("Enter X->");
    scanf("%lf",&x);
    return x;
}
double gety(){
    double y;
    printf("Enter Y->");
    scanf("%lf",&y);
    return y;
}
void calculate_myF(){
    double x,y,F;
    x=getx();
    y=gety();
    F=my_F(x,y);
    printf("X=%f,Y=%f,F(X,Y)=%f\n", x, y, F);
}
void wait(){
    printf("\n press 0 to quit\n");
    int c=0;
    scanf("%d",&c);
}

int main(int argc, const char * argv[]) {
    calculate_myF();
    calculate_myF();
    wait();
}
