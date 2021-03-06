#include<cstdio>
#include<cstdlib>
#include<cassert>
#include"cpu.hxx"
#include"stack.hxx"
#include"ram.hxx"
#include"newstack.hxx"
#include"codes.hxx"

using namespace std;

void cpu :: add() {
	double a;
	double b;
	checkerrors(stack.Pop(&a));
	checkerrors(stack.Pop(&b));
	checkerrors(stack.Push(a+b));
}

void cpu :: sub() {
	double a;
	double b;
	checkerrors(stack.Pop(&a));	
	checkerrors(stack.Pop(&b));
	checkerrors(stack.Push(a-b));
}

void cpu :: mul() {
	double a;
	double b;
	checkerrors(stack.Pop(&a));
	checkerrors(stack.Pop(&b));
	checkerrors(stack.Push(a*b));
}

void cpu :: div() {
	double a;
	double b;
	checkerrors(stack.Pop(&a));
	checkerrors(stack.Pop(&b));
	checkerrors(stack.Push(a/b));
}


cpu :: cpu(unsigned int ram_size,unsigned int stack_size) :
	ram(ram_size),
	stack(&esp,&ram,stack_size)
	{}

void cpu :: nocommand() {}

int cpu :: read_reg(unsigned int code) {
	if(code) {
		switch(code) {
			case 21 :
			return eax.d;
			break;
			
			case 22 :
			return ebx.d;
			break;
			
			case 23 :
			return ecx.d;
			break;

			case 24 :
			return edx.d;
			break;
			
			case 25:
			return eip.d;
			break;
			
			case 26:
			return ebp.d;
			break;
			
			case 27:
			return esp.d;
			break;
				
			default :
			fprintf(stderr,"Its unuseful %d code \n",code);
			break;
		}
	} else fprintf(stderr,"we have not a register in this %d code \n",code); 			
}

void cpu :: write_reg(unsigned int code,double element) {
	if(code) {
                switch(code) {
                        case 21 :
                        eax.d = element;
                        break;

                        case 22 :
                        ebx.d = element;
                        break;

                        case 23 :
                        ecx.d = element;
                        break;

                        case 24 :
                        edx.d = element;
                        break;
	
			case 25 :
			eip.d = element;
			break;

			case 26 :
			ebp.d = element;
			break;

			case 27 :
			esp.d = element;
			break;

                        default :
               //         fprintf(stderr,"Its unuseful %d code 3\n",code);
                        break;
                }
        } else fprintf(stderr,"we have not a register in this %d code 3\n",code);
}


void cpu :: push_reg_all() {
		unsigned int code;
		if(code && code >= 21 && code <= 27) {
			checkerrors(stack.Push(read_reg(code)));
			
		}
}
			

int cpu ::   read_arg(double* data) {
	int code;
	code = ram.Read_I((unsigned int)eip.d++);
	switch(code) {
		case r_code :
		*data = read_reg((unsigned int)ram.Read_I((unsigned int)eip.d++));
		return 1;
			
		case a_code :
		*data = ram.Read_D((unsigned int)ram.Read_I((unsigned int)eip.d)); 
		eip.d = eip.d + 1;
		return 1;

		case ra_code :
		*data = ram.Read_D(read_reg((unsigned int)ram.Read_I((unsigned int)eip.d)));
		eip.d = eip.d + 1;
		
		case num_d :
		*data = ram.Read_D((unsigned int)eip.d);
		eip.d = eip.d + 1;    
		return 1;
		
		default :
	//	fprintf(stderr,"Unknown argument %d\n",code);
		return 0;
	}
}

double cpu :: give_arg() {
	double* data;
	int c = 0;
	data = (double*)calloc(1,sizeof(double));
	c = read_arg(data);
	if (c == 1) { 
		return *data;
	} else { fprintf(stderr,"Bad arg\n");
	}
	
}
void cpu :: push() {
	checkerrors(stack.Push(give_arg()));
}
		
int cpu :: write_arg(double data) {	
	int  code;
	code = ram.Read_I((unsigned int)eip.d++);
        switch(code) {
                case r_code :
                write_reg((unsigned int)ram.Read_I((unsigned int)eip.d),data);
		eip.d = eip.d +1;
		return 1;

                case a_code :
                ram.Write_D((unsigned int)ram.Read_I((unsigned int)eip.d),data);
                eip.d = eip.d + 1;    
		return 1;         

		case ra_code :
		ram.Write_D(read_reg((unsigned int)ram.Read_I((unsigned int)eip.d)),data);       
                
		case num_d :
		fprintf(stderr,"it's not an address %d\n",code);
		break;

		case num_i :
		fprintf(stderr,"it's not an addressi%d\n",code) ;
		break;

		case in_tr:
		eip.d = eip.d + 1;
		break;          
                
		default :
		fprintf(stderr,"we have no argument for writing %d\n",code);
		break;
	}
}

void cpu :: pop(){
	double data;
	checkerrors(stack.Pop(&data));
	write_arg(data);
}
void cpu :: jmp() {
 	eip.d = give_arg();
}


void cpu :: ja() {
	double val;
	checkerrors(stack.Copy(&val));
	if(val > 0) {
		jmp();
	} else eip.d = eip.d + 2;
}

void cpu :: jae() {
        double val;
	checkerrors(stack.Copy(&val));                                                                             
        if(val >= 0) {                                                                           
                jmp();                                                                          
        } else eip.d = eip.d + 2;
}                

void cpu :: jb() {
        double val;                   
	checkerrors(stack.Copy(&val));                                                          
        if(val < 0) {                                                                           
                jmp();                                                                          
        } eip.d = eip.d +2;
}               

void cpu :: jbe() {
        double val;                 
	checkerrors(stack.Copy(&val));                                                            
        if(val <= 0) {                                                                           
                jmp();                                                                          
        } else eip.d = eip.d + 2;
}                
void cpu :: je() {
        double val; 
	checkerrors(stack.Copy(&val));                                                                            
        if(val == 0) {                                                                           
                jmp();                                                                          
        } eip.d = eip.d + 2;
}                                                                                         
void cpu :: jhe() {
	double val;
	checkerrors(stack.Copy(&val));                                                                            
        if(val != 0) {                                                                           
                jmp();                                                                          
        } eip.d = eip.d + 2;
}

void cpu :: call() {
	eip.d = eip.d + 1 ;
	checkerrors(stack.Push(eip.d));
	jmp();
}

void cpu :: ret() {
	stack.Pop(&eip.d);
}

void cpu :: ja_new() {
	double val1;
	double val2;
	checkerrors(stack.Pop(&val1));
	checkerrors(stack.Pop(&val2));
	if(val1 > val2) {
		jmp();
	} else eip.d = eip.d + 2;
}

void cpu :: jae_new() {
        double val1;
        double val2;
        checkerrors(stack.Pop(&val1));
        checkerrors(stack.Pop(&val2));
        if(val1 >= val2) {
                jmp();
        } else eip.d = eip.d + 2;
}

void cpu :: jb_new() {
        double val1;
        double val2;
        checkerrors(stack.Pop(&val1));
        checkerrors(stack.Pop(&val2));
        if(val1 < val2) {
                jmp();
        } else eip.d = eip.d + 2;
}

void cpu :: jbe_new() {
        double val1;
        double val2;
        checkerrors(stack.Pop(&val1));
        checkerrors(stack.Pop(&val2));
        if(val1 <= val2) {
                jmp();
        } else eip.d = eip.d + 2;
}

void cpu :: je_new() {
        double val1;
        double val2;
        checkerrors(stack.Pop(&val1));
        checkerrors(stack.Pop(&val2));
        if(val1 == val2) {
                jmp();
        } else eip.d = eip.d + 2;
}

void cpu :: jhe_new() {
        double val1;
        double val2;
        checkerrors(stack.Pop(&val1));
        checkerrors(stack.Pop(&val2));
        if(val1 != val2) {
                jmp();
        } else eip.d = eip.d + 2;
}

void cpu :: freee() {		
	eip.d = 0;
	eax.d = 0;
	ebx.d = 0;
	ecx.d = 0;
	edx.d = 0;	
	esp.d = 0;
}

void cpu :: load(FILE* f_in) {
	ram.entry(f_in);
}
		                             
double cpu :: out() {
	double loc;
	stack.Copy(&loc);
	eip.d = eip.d + 1;
	
}

void cpu :: in() {
	double val;
	scanf("%lg",&val);
	stack.Push(val);
//	write_arg(val);
	eip.d = eip.d +1;
	
}	

void cpu :: exit() {
	}
int cpu :: qualifier() {
	int code = 0;
	double a;
	code = ram.Read_I((unsigned)eip.d);
	eip.d = eip.d + 1;
	switch(code) {
		case PUSH :
			push();
			return 1;
			break;
		case POP :
			pop();
			return 1;
			break;
		case ADD :
			add();
			return 1;
			break;
		case MULL : 
			mul();
			return 1;
			break;
 		case SUB :
			sub();
			return 1;
			break;
		case DIV :
			div();
			return 1;
			break;
		case IN :
			in();
			return 1;
			break;
		case OUT :
			out();
			return 1;
			break;
		case PUSH_REG_ALL :
			push_reg_all();
			return 1;
			break;
		case JMP :
			jmp();
			return 1;
			break;
		case JA :
			ja();
			return 1;
			break;
		case JAE :
			jae();
			return 1;
			break;
		case JB :
			jb();
 			return 1;
			break;
		case JBE :
			jbe();
 			return 1;
			break;
		case JE :
			je();
			return 1;
			break;
		case JHE :
			jhe();
			return 1;
			break;
		case JA_NEW :
                        ja_new();
                        return 1;
                        break;
                case JAE_NEW :
                        jae_new();
                        return 1;
                        break;
                case JB_NEW :
                        jb_new();
                        return 1;
                        break;
                case JBE_NEW :
                        jbe_new();
                        return 1;
                        break;
                case JE_NEW :
                        je_new();
			return 1;
                        break;
                case JHE_NEW :
                        jhe_new();
                        return 1;
                        break;

		case CALL :
			call();
			return 1;
			break;
		case RET :
			ret();
			return 1;
			break;
		case FREEE : 
			freee();
			return 1;
			break;
		case EXIT :
			return 0;
			break;
		default :
			fprintf(stderr,"Unknown function%d\n",code);
			return 0;
			break;
		}
}


	

int main(int argc,char** argv) {
	FILE* f1 = NULL;
	char* name_in = "f_out.txt";
	f1 = fopen(name_in,"rb");
	fseek(f1,0,SEEK_SET);
	double value;
	int ram_size = RAM_SIZE;
	int stack_size = STACK_SIZE;
	double hui;
	fprintf(stderr,"We've started\n");
	cpu cpu_one(ram_size,stack_size);
	switch(argc - 1) {
		case 1:
			argv[1] = name_in;
			break;
		default :
			fprintf(stderr,"Wrong try to compile our programm\n");
			break;
		}
	cpu_one.load(f1);
	cpu_one.freee();
	while(cpu_one.qualifier()){;}
	fprintf(stderr,"out element = 120 \n");
	return 0;
}

	
