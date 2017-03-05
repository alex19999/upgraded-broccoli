#include<cstdio>
#include<cstdlib>
#include<cassert>
#include"cpu.hxx"

using namespace std;

int Ram :: Read_I(unsigned int addr) {
	if(addr) {
		if(addr + sizeof(int)/sizeof(char) => RAM_SIZE) {
			fprintf(stderr,"we can't read int from this %d adrress\n",addr);
			}
		return *((int*)&data_[addr]);
		} else return -1;
	}

double Ram :: Read_D(unsigned int addr) {
	if(addr) {
		if(addr+ sizeof(double)/sizeof(char) >= RAM_SIZE) {
			fprintf(stderr,"we can't read double from this %d address\n",addr);
			}
		return *((double*)&data_[addr]);
		} else return -1;
	}

char Ram :: Read_C(unsigned int addr) {
	if(addr) {
		if(addr-1 >= RAM_SIZE) {
			fprintf(stderr,"we can't read char from this %d address\n",addr);
			}
		return *((char*)&data_[addr]);
		} else return -1;
	}


int Ram :: Write_I(unsigned int addr) {                                                          
	int element;
	if(addr) {                                                                                            if(addr + sizeof(int)/sizeof(char) => RAM_SIZE) {                               
                       fprintf(stderr,"we can't write int in this %d adrress\n",addr);                                }
		&element = addr;
		return 1;		
     } else return -1;
}
int Ram :: Write_D(unsigned int addr) {                                                       
          double element;
	  if(addr) {
                if(addr+ sizeof(double)/sizeof(char) >= RAM_SIZE) {                             
                        fprintf(stderr,"we can't read double from this %d address\n",addr);     
                        }
                &element = (double)addr;
         } else return -1;
}
        
int  Ram :: Write_C(unsigned int addr) {
        char element;
	if(addr) {
                if(addr-1 >= RAM_SIZE) {                                                        
                        fprintf(stderr,"we can't read char from this %d address\n",addr);       
                        }                                                                       
                &element = (char)addr;
               } else return -1;                                                               
}






void Ram :: entry(FILE* f_in) {
	char* name_in;
	name_in = "text1.txt";
	f_in = fopen(name_in,"r");
	fscanf(f_in,"%d%c%lf",data_);
	}
Ram :: Ram(unsigned int capacity) {
	capacity_(capacity),
	size_(0)
	{
	data_ = calloc(sizeof(char),capacity);
	}
}
Ram :: ~Ram {
	free(data_);
}

void cpu :: add() {
	double a;
	double b;
	checkerrors(Stack.pop(a));
	checkerrors(Stack.pop(b));
	checkerrors(Stack.push(a+b));

}

void cpu :: sub() {
	double a;
	double b;
	checkerrors(Stack.pop(a));	
	checkerrors(Stack.pop(b));
	checkerrors(Stack.push(a-b));
}

void cpu :: mul() {
	double a;
	double b;
	checkerrors(Stack.pop(a));
	checkerrors(Stack.pop(b));
	checkerrors(Stack.push(a*b));
	}

void cpu :: div() {
	double a;
	double b;
	checkerrors(Stack.pop(a));
	checkerrors(Stack.pop(b));
	checkerrors(Stack.push(a/b));
}

void cpu :: in() {
	fprintf(stdout,"please,give me your elements\n");
	fscanf(stdin,"%d%c%lf",stack->data_);
}

double cpu :: out() {
	double a;
	checkerrors(Stack.pop(&a));
	return a;
}

cpu :: cpu(unsigned int capacity) {
	capacity_(capacity),
	size_()
	{
	data =(double*)calloc(sizeof(double,capacity_);
	}
}

cpu :: ~cpu() {
	free(data_);
	}


int Ram :: read_regI(unsigned int code) {
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

double Ram :: read_regD(unsigned int code) {
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


void Ram :: write_regI(unsigned int code) {
        int element;
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


void Ram :: write_regD(unsigned int code) {
	double element;
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

void cpu :: push_reg_all(int code) {
		if(code && code >= 0x01 && code <= 0x04) {
			checkerrors(Stack.push((double)read_regI(code)));
			checkerrors(Stack.push(read_regD(code)));
		}
}
			

int cpu ::   read_arg(void* data) {
	char code;
	code = Ram.Read_C((unsigned int)eip.i++);
	switch(code) {
		case reg_codeI :
		*((int*)data) = Ram.read_regI((unsigned int)Read_C((unsigned int)eip.i++));
		return 1;
		
		case reg_codeD :
		*((double*)data) = Ram.read_regD((unsigned int)Read_C((unsigned int)eip.i++i));			return 2;
			
		case add_codeI :
		*((int*)data) = Ram.Read_I((unsigned int)Read_I((unsigned int)eip.i)); 
		eip.i = eip.i + (unsigned int)(sizeof(int)/sizeof(char));
		return 1;
		
		case add_codeD :
		*((double*)data) = Ram.Read_D((unsigned int)Read_I((unsigned int)eip.i)); 
		eip.i = eip.i + (unsigned int)(sizeof(double)/sizeof(char));
		return 2;

		case num_i :
		*((int*)data) = Ram.Read_I((unsigned int)eip.i)); 
		eip.i = eip.i + (unsigned int)(sizeof(int)/sizeof(char));
		return 1;
		
		case num_d :
		*((double*)data) = Read_D((unsigned int)eip.i));
		eip.i = eip.i + (unsigned int)(sizeof(double)/sizeof(char));    
		return 2;
		
		default :
		fprintf(stderr,"Unknown argument\n",code);
	}
}

void cpu :: push_reg() {
	int c;
	void* data;
	data = calloc(1,sizeof(double);
	c = read_arg(data);
	if(c == 1) {
		Stack.push((double)*(int*)data);
	} else {
		Stack.push(*((double*)data));
		}

}
		
int cpu :: write_arg(void* data) {	
char code;
code = Ram.Read_C((unsigned int)eip.i++);
        switch(code) {
                case reg_codeI :
                *((int*)data) = Ram.write_regI((unsigned int)Read_C((unsigned int)eip.i++)));
		return 1;

                case reg_codeD :
	       *((double*)data) = Ram.write_regD((unsigned int)Read_C((unsigned int)eip.i++)));
		return 2;
	
                case add_codeI :
                *((int*)data) =  Ram.Write_I((unsigned int)Read_I((unsigned int)eip.i)));
                eip.i = eip.i + (unsigned int)(sizeof(int)/sizeof(char));    
		return 1;                      
               	                                                                             
                case add_codeD :                                                               
                *((double*)data) =  Ram.Write_D((unsigned int)Read_I((unsigned int)eip.i));      
                eip.i = eip.i + (unsigned int)(sizeof(double)/sizeof(char));  
		return 2;
                
		case mum_i :
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
		checkerrors(Stack.pop((double*)data);
		}
	else checkerrors(Stack.pop(data);
}
	
void cpu :: jmp() {
	






