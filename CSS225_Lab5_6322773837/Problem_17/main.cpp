//
//  main.cpp
//  Problem_17
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//
#include <iostream>
#include <stdlib.h>
#include <math.h>

int getvar(){//inputs an arbitrary int variable
    int var;
    printf("select a product (771, 882, 547, 511, 225)->");
    scanf("%d",&var);
    return var;
}

void wait(){
    printf("press 0 to continue\n");
    int c;
    scanf("%d",&c);
}


int main(int argc, const char * argv[]) {
    int n, unit;
    n=getvar();
    switch (n)
    {
        case 771:
            printf("enter the # of units : ");
            scanf("%d",&unit);
            printf("discount=%d\n",0);
            printf("you pay only %d.\n",100*unit);
        case 882:
            printf("enter the # of units : ");
            scanf("%d",&unit);
            printf("discount=%d\n",30*unit);
            printf("you pay only %d.\n",270*unit);
            break;
        case 547:
            printf("enter the # of units : ");
            scanf("%d",&unit);
            printf("discount=%.2f\n",150*0.05*unit);
            printf("you pay only %.2f.\n",150*0.95*unit);
            break;
        case 511:
            printf("enter the # of units : ");
            scanf("%d",&unit);
            printf("discount=%d\n",10*unit);
            printf("you pay only %d.\n",190*unit);
            break;
        case 225:
            printf("enter the # of units : ");
            scanf("%d",&unit);
            printf("discount=%d\n",150*unit);
            printf("you pay only %d.\n",850*unit);
            break;
        default:
            printf("wrong product code\n");
    };//end of switch
        wait();
}
