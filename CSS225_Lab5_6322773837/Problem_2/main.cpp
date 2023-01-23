//
//  main.cpp
//  Problem_2
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    int integer1, integer2, sum;
    printf("Enter the first integer : ");
    scanf("%d",&integer1);
    printf("Enter the second integer : ");
    scanf("%d",&integer2);
    sum = integer1 + integer2;
    printf("%d + %d =%d\n", integer1, integer2, sum);
    printf("press 0 to quit\n");
    int c;
    scanf("%d",&c);
    return 0;
}
