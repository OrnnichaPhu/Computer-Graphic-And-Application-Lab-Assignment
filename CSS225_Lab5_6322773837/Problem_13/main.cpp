//
//  main.cpp
//  Problem_13
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
#include<stdlib.h>

void evaluate(int a,int b){
    if (b==0){
        printf("division by zero\n");
        exit(0);
    }
    else
        printf("Result->%1f",(double)a/b);
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
    int a,b;
    a=getvar('a');
    b=getvar('b');
    evaluate(a,b);
    wait();
    a=getvar('a');
    b=getvar('b');
    evaluate(a,b);
    wait();
}
