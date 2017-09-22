#include<cstdlib>
#include<cstdio>
#include<iostream>
#include"ram.hxx"

using namespace std;

int Ram :: Read_I(unsigned int addr) {
        if(addr >= 0) {
                if(addr >= size_) {
                        return -1;
                        }
                return (int)data_[addr];
        }
}

double Ram :: Read_D(unsigned int addr) {
        if(addr >= 0 ) {
                if(addr + 1  >= size_) {
                        fprintf(stderr,"we can't read double from this %d address\n",addr);
                        return -1;
                        }
                return data_[addr];
        }
}

char Ram :: Read_C(unsigned int addr) {
        if(addr >= 0) {
                if(addr >= size_) {
                        fprintf(stderr,"we can't read char from this %d address\n",addr);
                        return -1;
                        }
                return (char)data_[addr];
        }
}

int Ram :: Write_I(unsigned int addr,int element) {
        if(addr >= 0) {
                if(addr >= size_) {
                        fprintf(stderr,"we can't write int in this %d adrress\n",addr);
                }
                data_[addr] = (double)element ;
                return 1;
     } else return -1;
}

int Ram :: Write_D(unsigned int addr,double element) {
          if(addr >= 0) {
                if(addr+1 >= size_) {
                        fprintf(stderr,"we can't read double from this %d address\n",addr);
                        }
                data_[addr] = element;
                return 1;
         } else return -1;
}

int  Ram :: Write_C(unsigned int addr,char element) {
        if(addr >= 0) {
                if(addr >= size_) {
                        fprintf(stderr,"we can't read char from this %d address\n",addr);
                        }
                data_[addr] = (double)element;
                return 1;
               } else return -1;
}

void Ram :: entry(FILE* f_in) {
        int n = 0;
        while(!feof(f_in)) {
        fscanf(f_in,"%lg",&data_[n++]);
        }
}


Ram :: Ram(unsigned int ramsize) :
        size_(ramsize)
        {
        data_ =(double*)calloc(ramsize,sizeof(double));

}

Ram :: ~Ram() {
        free(data_);
}

