//
//  main.cpp
//  Problem_16
//
//  Created by Ornnicha Phueaksri on 18/2/2565 BE.
//

#include <iostream>


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

void evaluate(int n){
        switch (n){
            case 1: printf("--------------------outputX = %d--------------------\n",n);
                break;
            case 2:printf("--------------------outputX = %d--------------------\n",n);
                break;
            case 5:printf("--------------------outputX = %d--------------------\n",n);
                break;
            default:printf("**********wrong input************\n");
        };//end of switch
    wait();
}

int main(int argc, const char * argv[]) {
    
    int n;
    n=getvar('n');
    evaluate(n);
    n=getvar('n');
    evaluate(n);

}
