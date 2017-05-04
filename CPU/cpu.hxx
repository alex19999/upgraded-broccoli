#ifndef _CPU_H_
#define _CPU_H_

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<iostream>
#include"stack.hxx"
#include"ram.hxx"
#include"newstack.hxx"

class cpu {
	public:
	cpu(unsigned int ram_size,unsigned int stack_size);
	void load(FILE* f_in);
	void freee();
	int qualifier();
	private:
	reg eax;
	reg ebx;
	reg ecx;
	reg edx;
	reg eip;
	reg ebp;
	reg esp;
	double* data_;
	int read_reg(unsigned int code);
        void write_reg(unsigned int code,double element);
	Ram ram;
	NewStack stack;
	void push();
	void pop();
	void push_reg_all();
	void nocommand();
	int read_arg(double* data);
	int write_arg(double data);
	double give_arg();
	void push_reg();
	void add();
	void mul();
	void sub();
	void div();
	void in();
	void jmp();
	void ja();
	void jae();
	void jb();
	void jbe();
	void je();
	void ja_new();
	void jae_new();
	void jb_new();
	void jbe_new();
	void je_new();
	void jhe_new();
	double out();
	void jhe();
	void call();
	void ret();
	void exit();
};




#endif /* _CPU_H_ */
