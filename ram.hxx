#ifndef _RAM_H_
#define _RAM_H_

#include<cstdlib>
#include<cstdio>

union reg {
        double d;
};

class Ram {
        private:
        double* data_;
        public:
        int Read_I(unsigned int addr);
        double Read_D(unsigned int addr);
        char Read_C(unsigned int addr);
        int Write_I(unsigned int addr,int element);
        int Write_D(unsigned int addr,double element);
        int Write_C(unsigned int addr,char element);
        void entry(FILE* f_in);
        unsigned int size_;
        Ram(unsigned int ramsize);
        ~Ram();
        };


#endif /*_RAM_H_*/

