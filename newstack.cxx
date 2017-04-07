#include<cstdio>
#include<cstdlib>
#include<iostream>
#include"ram.hxx"
#include"newstack.hxx"

using namespace std;


unsigned int NewStack :: Push(double val){
        esp->d = esp->d + 1;
        if (esp->d <  maxsize_ - 1){
                 ram->Write_D((unsigned)esp->d,val);

        }  else {
                return 0;
                printf("ram->size_=%u\nmaxsize=%d\nesp->d=%lg\n",ram->size_, maxsize_, esp->d);
                }
        return 5;
}
unsigned int NewStack :: Pop(double* loc){
        if (esp->d <= ram->size_- 1) {
                *loc = ram->Read_D((unsigned)esp->d);
                 fprintf(stderr,"popping  elem = %lg\n",*loc);
                }
        esp->d = esp->d - 1;
        fprintf(stderr,"popping  elem = %lg\n",*loc);
        return 0;
}

unsigned int NewStack :: Copy(double* loc){
        if (esp->d <= ram->size_ - 1){
                *loc = ram->Read_D((unsigned)esp->d);
                fprintf(stderr,"our copying element\n");
                }

        return 0;
}

NewStack :: NewStack(reg* esp1, Ram* ram1, int stacksize):
        esp(esp1),
        ram(ram1),
        maxsize_(stacksize)
{}

