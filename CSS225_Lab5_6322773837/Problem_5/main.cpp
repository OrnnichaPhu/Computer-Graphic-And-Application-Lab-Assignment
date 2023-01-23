//
//  main.cpp
//  Problem_5
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
#include <math.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    double x,y,f;
    printf("Enter x->");
    scanf("%lf",&x);
    printf("Enter y->");
    scanf("%lf",&y);
    f=1+(pow(sin(x),2)+pow(sin(2*x),2));
    f/=sqrt(cos(6*x)+pow(x, 3)-tan(y));
    printf("f=%lf\n",f);
    return 0;
}
