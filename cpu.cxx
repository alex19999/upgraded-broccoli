#include<cstdio>
#include<cstdlib>
#include<cassert>
#include"cpu.hxx"
#include"stack.hxx"

using namespace std;

int Ram :: Read_I(unsigned int addr) {
	if(addr) {
		if(addr + sizeof(int)/sizeof(char) >= RAM_SIZE) {
			fprintf(stderr,"we can't read int from this %d adrress\n",addr);
			}
		return *((int*)(&((char*)data_)[addr]));
		} else return -1;
	}

double Ram :: Read_D(unsigned int addr) {
	if(addr) {
		if(addr+ sizeof(double)/sizeof(char) >= RAM_SIZE) {
			fprintf(stderr,"we can't read double from this %d address\n",addr);
			}
		return *((double*)(&((char*)data_)[addr]));
		} else return -1;
	}

char Ram :: Read_C(unsigned int addr) {
	if(addr) {
		if(addr-1 >= RAM_SIZE) {
			fprintf(stderr,"we can't read char from this %d address\n",addr);
			}
		return ((char*)data_)[addr];
		} else return -1;
	}


int Ram :: Write_I(unsigned int addr) {                                                          
	int element;
	if(addr) {        
		if(addr + sizeof(int)/sizeof(char) >= RAM_SIZE) {                               
                       fprintf(stderr,"we can't write int in this %d adrress\n",addr);                                
			}
		element = *((int*)(&((char*)data_)[addr])) ;
		return 1;		
     } else return -1;
}
int Ram :: Write_D(unsigned int addr) {                                                       
          double element;
	  if(addr) {
                if(addr+ sizeof(double)/sizeof(char) >= RAM_SIZE) {                             
                        fprintf(stderr,"we can't read double from this %d address\n",addr);     
                        }
                element = *((double*)(&((char*)data_)[addr]));
		return 1;
         } else return -1;
}
        
int  Ram :: Write_C(unsigned int addr) {
        char element;
	if(addr) {
                if(addr-1 >= RAM_SIZE) {                                                        
                        fprintf(stderr,"we can't read char from this %d address\n",addr);       
                        }                                                                       
                element = ((char*)data_)[addr];
		return 1;
               } else return -1;                                                               
}


void Ram :: entry(FILE* f_in) {
	char* name_in;
	name_in = "text1.txt";
	f_in = fopen(name_in,"r");
	fscanf(f_in,"%s",(char*)data_);
	}
Ram :: Ram(unsigned int capacity) {
		data_ =(void*) calloc(sizeof(char),capacity);
	
}
Ram :: ~Ram() {
	free(data_);
}

void cpu :: add() {
	double a;
	double b;
	checkerrors(stack.pop(&a));
	checkerrors(stack.pop(&b));
	checkerrors(stack.push(a+b));

}

void cpu :: sub() {
	double a;
	double b;
	checkerrors(stack.pop(&a));	
	checkerrors(stack.pop(&b));
	checkerrors(stack.push(a-b));
}

void cpu :: mul() {
	double a;
	double b;
	checkerrors(stack.pop(&a));
	checkerrors(stack.pop(&b));
	checkerrors(stack.push(a*b));
	}

void cpu :: div() {
	double a;
	double b;
	checkerrors(stack.pop(&a));
	checkerrors(stack.pop(&b));
	checkerrors(stack.push(a/b));
}

void cpu :: in() {
	int k;
	int i;
	double m;
	fprintf(stdout,"please,give me the number %d of your elements\n",k);
	if(k > 0) {
		for(i == 1; i <= k; i++) {
 			fscanf(stdin,"%lf",&m);
			checkerrors(stack.push(m));

		}
	}
}

double cpu :: out() {
	double a;
	checkerrors(stack.pop(&a));
	return a;
}

cpu :: cpu() :
	
	ram(RAM_SIZE),
	stack((size_t)STACK_SIZE),
	callstack((size_t)CALLSTACK_SIZE) 

	{}

//cpu :: ~cpu() {
//	free(data_);
//	}


int cpu :: read_regI(unsigned int code) {
	if(code) {
		switch(code) {
			case 0x01 :
			return eax.i;
			break;
			
			case 0x02 :
			return ebx.i;
			break;
			
			case 0x03 :
			return ecx.i;
			break;

			case 0x04 :
			return edx.i;
			break;
			
			case 0x05:
			return eip.i;
			break;
				
			default :
			fprintf(stderr,"Its unuseful %d code 1\n",code);
			break;
		}
	} else fprintf(stderr,"we have not a register in this %d code 1\n",code); 			
}

double cpu :: read_regD(unsigned int code) {
        if(code) {
                switch(code) {
                        case 0x01 :
                        return eax.d;
                        break;

                        case 0x02 :
                        return ebx.d;
                        break;

                        case 0x03 :
                        return ecx.d;
                        break;

                        case 0x04 :
                        return edx.d;
                        break;

			case 0x05 :
			return eip.d;
			break;
		
                        default :
                        fprintf(stderr,"Its unuseful %d code 2\n",code);
                        break;
                }
        } else fprintf(stderr,"we have not a register in this %d code 2\n",code);
}


void cpu :: write_regI(unsigned int code,int element) {
        
	if(code) {
                switch(code) {
                        case 0x01 :
                        eax.i = element;
                        break;

                        case 0x02 :
                        ebx.i = element;
                        break;

                        case 0x03 :
                        ecx.i = element;
                        break;

                        case 0x04 :
                        edx.i = element;
                        break;

                        default :
                        fprintf(stderr,"Its unuseful %d code 3\n",code);
                        break;
                }
        } else fprintf(stderr,"we have not a register in this %d code 3\n",code);
}


void cpu :: write_regD(unsigned int code,double element) {
        if(code) {
                switch(code) {
                        case 0x01 :
                        eax.d = element;
                        break;

                        case 0x02 :
                        ebx.d = element;
                        break;

                        case 0x03 :
                        ecx.d = element;
                        break;

                        case 0x04 :
                        edx.d = element;
                        break;

                        default :
                        fprintf(stderr,"Its unuseful %d code 4\n",code);
                        break;
                }
        } else fprintf(stderr,"we have not a register in this %d code 4\n",code);
}

void cpu :: push_reg_all(unsigned int code) {
		if(code && code >= 0x01 && code <= 0x04) {
			checkerrors(stack.push((double)read_regI(code)));
			checkerrors(stack.push(read_regD(code)));
		}
}
			

int cpu ::   read_arg(void* data) {
	char code;
	code = ram.Read_C((unsigned int)eip.i++);
	switch(code) {
		case reg_codeI :
		*((int*)data) = read_regI((unsigned int)ram.Read_C((unsigned int)eip.i++));
		return 1;
		
		case reg_codeD :
		*((double*)data) = read_regD((unsigned int)ram.Read_C((unsigned int)eip.i++));
		return 2;
			
		case add_codeI :
		*((int*)data) = ram.Read_I((unsigned int)ram.Read_I((unsigned int)eip.i)); 
		eip.i = eip.i + (unsigned int)(sizeof(int)/sizeof(char));
		return 1;
		
		case add_codeD :
		*((double*)data) = ram.Read_D((unsigned int)ram.Read_I((unsigned int)eip.i)); 
		eip.i = eip.i + (unsigned int)(sizeof(double)/sizeof(char));
		return 2;

		case num_i :
		*((int*)data) = ram.Read_I((unsigned int)eip.i); 
		eip.i = eip.i + (unsigned int)(sizeof(int)/sizeof(char));
		return 1;
		
		case num_d :
		*((double*)data) = ram.Read_D((unsigned int)eip.i);
		eip.i =eip.i + (unsigned int)(sizeof(double)/sizeof(char));    
		return 2;
		
		default :
		fprintf(stderr,"Unknown argument\n",code);
	}
}

void cpu :: push_reg() {
	int c;
	void* data;
	data = calloc(1,sizeof(double));
	c = read_arg(data);
	if(c == 1) {
		stack.push((double)*(int*)data);
	} else {
		stack.push(*((double*)data));
		}

}
		
int cpu :: write_arg(void* data) {	
char code;
code = ram.Read_C((unsigned int)eip.i++);
        switch(code) {
                case reg_codeI :
                write_regI((unsigned int)ram.Read_C((unsigned int)eip.i++),*((int*)data));
		return 1;

                case reg_codeD :
	        write_regD((unsigned int)ram.Read_C((unsigned int)eip.i++),*((double*)data));
		return 2;
	
                case add_codeI :
                *((int*)data) =  ram.Write_I((unsigned int)ram.Read_I((unsigned int)eip.i));
                eip.i = eip.i + (unsigned int)(sizeof(int)/sizeof(char));    
		return 1;                      
               	                                                                             
                case add_codeD :                                                               
                *((double*)data) =  ram.Write_D((unsigned int)ram.Read_I((unsigned int)eip.i));      
                eip.i = eip.i + (unsigned int)(sizeof(double)/sizeof(char));  
		return 2;
                
		case num_d :
		fprintf(stderr,"it's not an address",code);
		break;
		
		case num_i :
		fprintf(stderr,"it's not an address",code) ;
		break;          
                
		default :
		fprintf(stderr,"we have no argument for writing",code);
		break;
	}
}

void cpu :: pop_reg() {
	int c;
	void* data;
	data = calloc(1,sizeof(double));
	c = write_arg(data);
	if(c == 1) {
		checkerrors(stack.pop((double*)data));
		}
	else checkerrors(stack.pop((double*)data));
}
	
//void cpu :: jmp() {

