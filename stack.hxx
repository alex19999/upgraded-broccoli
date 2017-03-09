#ifndef _Stack_H_
#define _Stack_H_
#include<cstdio>
#include<cstdlib>


class Stack {

public: 

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
private:

	int capacity_;
	int size_;
	double* data_;

};
void checkerrors(int errornum);
#endif  /* _Stack_H_ */
