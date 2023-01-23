//
//  main.cpp
//  Problem_12
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
void evaluate(int a){
    if( a < 20 )
        printf("This number is less than 20\n" );
    else
        printf("This number is greater or equal to 20\n" );
    printf("This number is equal to : %d\n", a);
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
    int a, b;
    a=getvar('a');
    evaluate(a);
    b=getvar('b');
    evaluate(b);
    wait();
}
