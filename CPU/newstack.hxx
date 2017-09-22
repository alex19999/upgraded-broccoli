#ifndef _NEWSTACK_H_
#define _NEWSTACK_H_

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include"ram.hxx"



class NewStack {

        public:

        unsigned int Push(double value);
        unsigned int Pop(double* location);
        unsigned int Copy(double* location);
        NewStack(reg* esp,Ram* ram,int maxsize_);


        private:
        Ram* ram;
        reg* esp;
        int maxsize_;

};


#endif /*_NEWSTACK_H_*/
