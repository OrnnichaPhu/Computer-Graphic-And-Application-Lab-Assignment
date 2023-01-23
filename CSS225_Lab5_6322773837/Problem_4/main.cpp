//
//  main.cpp
//  Problem_4
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
#include <math.h>

int main(int argc, const char * argv[]) {
    double F,x;
    printf("Enter x->");
    scanf("%lf",&x);
    F=sin(x)+pow(x,2)+sqrt(x)+pow(sin(x),3);
    F/=x*x+1;
    printf("F= %lf\n",F);
    printf("press 0 to quit\n");
    int c; scanf("%d",&c);
    return 0;
}
