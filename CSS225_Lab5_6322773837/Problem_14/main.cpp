//
//  main.cpp
//  Problem_14
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
#include <math.h>

double my_F(double x){
    double a;
    a=sqrt(x)+sin(x)+sqrt(1-x);
    return a;
}
double getx(){
    double x;
    printf("Enter x->");
    scanf("%lf",&x);
    return x;
}

void evaluate(double x, double F){
    if ((x<0) || (x>1))
        printf("negative argument\n");
    else
        printf("F= %lf\n",F);
}

void calculate_myF(){
    double x, F;
    x=getx();
    F=my_F(x);
    evaluate(x,F);
}
void wait(){
    printf("\n press 0 to quit\n");
    int c=0;
    scanf("%d",&c);
}


int main(int argc, const char * argv[]) {
    calculate_myF();
    calculate_myF();
    calculate_myF();
    return 0;
}
