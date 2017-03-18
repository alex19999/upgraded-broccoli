#ifndef _CPU_H_
#define _CPU_H_

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<iostream>
#include"stack.hxx"

#define F_MAXLINE 6
#define ARG_MAXLINE 10
#define RAM_SIZE 128
#define STACK_SIZE 8
#define CALLSTACK_SIZE 16
#define NOCOMMAND 0x00
#define PUSH 0x10
#define POP 0x11
#define ADD 0x20
#define MUL 0x21
#define SUB 0x22
#define DIV 0x23
#define OUT 0x01             
#define IN 0x02
#define POP_REG 0x1a
#define PUSH_REG 0x1b
#define PUSH_REG_ALL 0x1c
#define JMP 0x31
#define JA  0x32
#define JAE 0x33
#define JB  0x34
#define JBE 0x35
#define JE  0x36
#define JHE 0x37
#define CALL 0x38
#define RET 0x39

#define R_eax 0x01
#define R_ebx 0x02
#define R_ecx 0x03
#define R_edx 0x04
#define R_eip 0x05

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
};

class Ram {
	private:
	void* data_;
	public:
	int Read_I(unsigned int addr);
	double Read_D(unsigned int addr);
	char Read_C(unsigned int addr);
	int Write_I(unsigned int addr);
	int Write_D(unsigned int addr);
	int Write_C(unsigned int addr);
	void entry(FILE* f_in);
	Ram(unsigned int capacity);
	~Ram();
	};


class cpu {
	public:
	Stack stack;
	Stack callstack;
	private:
	reg eax;
	reg ebx;
	reg ecx;
	reg edx;
	reg eip;
	double* data_;
	int read_regI(unsigned int code);
        double read_regD(unsigned int code);
        void write_regI(unsigned int code,int element);
        void write_regD(unsigned int code,double element);
	Ram ram;
	void push_reg_all();
	int read_arg(void* data);
	int write_arg(void* data);
	void push_reg();
	void pop_reg();
	void add();
	void mul();
	void sub();
	void div();
	void in();
	double out();
	void jmp();
	void ja();
	void jae();
	void jb();
	void jbe();
	void je();
	void jhe();
	void call();
	void ret();
	void qualifier();
	cpu();
	~cpu();
};

#endif /* _CPU_H_ */
