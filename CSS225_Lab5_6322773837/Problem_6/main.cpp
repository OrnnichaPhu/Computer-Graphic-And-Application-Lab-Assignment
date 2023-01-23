//
//  main.cpp
//  Problem_6
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
#include <math.h>

double my_F(double x){
    double a;
    a=sin(x)+pow(x,2)+sqrt(x)+pow(sin(x),3);
    return a;
}

double getx(){
    double x;
    printf("Enter x->");
    scanf("%lf",&x);
    return x;
}

int main(int argc, const char * argv[]) {
    double x,F;
    x=getx();
    F=my_F(x);
    printf("F= %lf\n",F);
    x=getx();
    F=my_F(x);
    printf("F= %lf\n",F);
    printf("\n press 0 to quit\n");
    int c=0;
    scanf("%d",&c);
}

