#ifndef _CPU_H_
#define _CPU_H_

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<iostream>


#define F_MAXLINE 6
#define ARG_MAXLINE 10
#define RAM_SIZE 128

#define NOCOMMAND 0x00
#define PUSH 0x10
#define POP 0x11
#define ADD 0x20
#define MUL 0x21
#define SUB 0x22
#define DIV 0x23
#define OUT 0x01             
#define IN 0x02
#define POPAX 0x1a
#define PUSHAX 0x1b

#define eax 0x01
#define ebx 0x02
#define ecx 0x03
#define edx 0x04
#define eip 0x05

#define reg_codeI 0x01
#define reg_codeD 0x02
#define add_codeI 0x03
#define add_codeD 0x04
#define num_i   0x05
#define num_d   0x06

#define reg_code 0x01
#define add_code 0x02
#define adres_prep 'h' 

union reg {
	int i;
	double d;
}

class Ram {
	private:
	void* data_;
	unsigned int size_
	unsigned int capacity_;
	public:
	int read_regI(unsigned int code);
	double read_regD(unsigned int code);
	int Read_I(unsigned int addr);
	double Read_D(unsigned int addr);
	char Read_C(unsigned int addr);
	int Write_I(unsigned int addr);
	int Write_D(unsigned int addr);
	int Write_C(unsigned int addr);
	void write_regI(unsigned int code);
	void write_regD(unsigned int code);
	void entry(FILE* f_in);
	Ram(unsigned int capacity);
	~Ram();
	}


class cpu {
	private:
	reg eax;
	reg ebx;
	reg ecx;
	reg edx;
	double* data_;
	unsigned int size_;
	unsigned int capacity_;
	Ram ram;
	Stack stack;
	void push_reg_all(unsigned int code);
	int read_arg(void* data);
	void push_reg();
	void pop_reg();
	void add();
	void mul();
	void sub();
	void div();
	void in();
	void out();
	cpu(unsigned int capacity);
	~cpu;
}

#endif /* _CPU_H_ */
