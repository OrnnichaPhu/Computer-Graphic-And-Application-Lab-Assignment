//
//  main.cpp
//  Problem_15
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>


int getvar(char a){//inputs an arbitrary int variable
    int var;
    printf("input %c->",a);
    scanf("%d",&var);
    return var;
}

void wait(){
    printf("press 0 to continue\n");
    int c;
    scanf("%d",&c);
}

int main(int argc, const char * argv[]) {
    int n; double f;
    n=getvar('n');
    switch (n){
        case 1:f=1;
            break;
        case 2:f=-1;
            break;
        case -3:f=0;
            break;
        default:
            if (n<0) {
                printf("negative n\n");
                wait();
                exit(0);
                
            }
        else
            f=sqrt(n)/(sin(n)+2);
    };//end of switch
    printf("f=%lf\n",f);
    wait();
}
