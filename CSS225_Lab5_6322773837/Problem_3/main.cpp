//
//  main.cpp
//  Problem_3
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    float integer1, integer2, sum;
    printf("Input : R1= ");
    scanf("%f",&integer1);
    printf("Input : R2= ");
    scanf("%f",&integer2);
    sum = integer1 * integer2;
    printf("Output : %.2f \n",sum);
    printf("press 0 to quit\n");
    int c;
    scanf("%d",&c);
    return 0;
}

