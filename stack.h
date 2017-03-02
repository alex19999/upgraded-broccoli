#ifndef _Stack_H_
#define _Stack_H_

class Stack;


unsigned int push(double value);

unsigned int pop(double* location);

unsigned int empty();

unsigned char Broke();

void dump(FILE* f);

int Capacity();

int getsize();

int verifypoint(void*p);

Stack(int capacity);

~Stack();

#endif /* _Stack_H_ */
