#include<cstdlib>
#include<cassert>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<malloc.h>


using namespace std;


#define F_MAXLINE 9
#define ARG_MAXLINE 10
#define RAM_SIZE 256
#define MAX_OP 256
#define STACK_SIZE 128
#define NOCOMMAND 0
#define PUSH 1
#define POP 2
#define ADD 3
#define MULL 4
#define SUB 5
#define DIV 6
#define OUT 7           
#define IN 8
#define POPR 9
#define PUSHR 10
#define PUSH_REG_ALL 30
#define JMP 11                                                                              
#define JA  12                                                                               
#define JAE 13                                                                              
#define JB  14                                                                              
#define JBE 15                                                                               
#define JE  17                                                                               
#define JHE 18                                                                              
#define CALL 19                                                                              
#define RET 20       
#define FREEE 16

#define R_eax 21
#define R_ebx 22
#define R_ecx 23
#define R_edx 24
#define R_eip 25
#define R_ebp 26
#define R_esp 27

#define r_code 1
#define a_code 2
#define num_i 3
#define num_d 4
#define ra_code 5
#define in_tr 6 
#define a_prep 'h' 

typedef struct _table1 {    				// table to collect our lables and their addresses//
        double go;
        int addr;
} table1;

typedef struct _table2 {				// table to convert our operarions//
	double* oper;
} table2;

double convert_arg(FILE* f1) {				// convertind arguements//
        char par;
        char* arg;
        arg = (char*)calloc(ARG_MAXLINE,sizeof(char));
        int i = 0;
        int f = 0;
        par = fgetc(f1);
        int val;
        double dval;
        fprintf(stderr,"START CONVERT\n");
        while(par && !isspace(par) && par != EOF) {
        if(i >= ARG_MAXLINE) {
                fprintf(stderr,"TOO LONG ARGUMENT%s\n",arg);
                return 0;
        }
                arg[i++] = par;
                if(isdigit(par)) {
                        if(f == 2) {
                                f = 3;
                        } else {
                                if (f == 0) {
                                        f = 1;
                                }
                        }
                } else
                        if(par == '.') {
                                if(f == 2 || f == 3) {
                                        f = 4;
                                } else {
                                        if(f == 1) {
                                                f = 2;
                                                }
                                        }

                } else {
                        f = 4;
                        }
                        par = fgetc(f1);
                }


        if (f == 1) {
		sscanf(arg,"%d",&val);
                return (double)val;
                }
        if(f == 3) {
                sscanf(arg,"%lf",&dval);
                return dval;
                }
        if(!strcmp(arg,"R_eax")) {
                return 21;
                }
        if(!strcmp(arg,"R_ebx")) {
                return 22;
                }
        if(!strcmp(arg,"R_ecx")) {
                return 23;
                }
        if(!strcmp(arg,"R_edx")) {
                return 24;
                }
	if(!strcmp(arg,"R_eip")) {                                                              
                return 25;                                                                      
                }           
        if(!strcmp(arg,"R_ebp")) {                                                              
                return 26;                                                                      
                }                                                                               
        if(!strcmp(arg,"R_esp")) {                                                              
                return 27;                                                                      
                }
	 if(!strcmp(arg,"r_code")) {
                return 1;
                }
	 if(!strcmp(arg,"a_code")) {
                return 2;
                }
	 if(!strcmp(arg,"num_i")) {
                return 3;
                }
	 if(!strcmp(arg,"num_d")) {
                return 4;
                }
	 if(!strcmp(arg,"ra_code")) {
                return 5;
                }
	if(!strcmp(arg,"in_tr")) {
		return 6;
                }                                                                                                                               
        if(arg[0] == 'h') {
                sscanf(&arg[1],"%d",&val);
                return val;
                }
	if(arg[0] == '*') {
		sscanf(&arg[1],"%lf",&dval);
		return dval;
		}
        if(!strcmp(arg,"")) {
                fprintf(stderr,"Please,give me some argument%s\n",arg);
                return 0;
                }

}



int create_table(FILE* f1,table1* t1,table2* t2) {	// create table of our programm and 
	fseek(f1,0,SEEK_SET);
	char k = 0 ;					
	int m = 0;					
       	char* process;				
        process = (char*)calloc(F_MAXLINE,sizeof(char));
        int i = 0;
	int n = 0;					
	int t = 0;					
	double dval1;
	double dval2;
	while(k != EOF) {
	i = 0;
	k = fgetc(f1);
        fprintf(stderr,"We continue to work\n");
        fprintf(stderr, "Reading sym %d\n", k);
        while (k && !isspace(k) && k!= EOF) {
                if (i >=F_MAXLINE) {
                        fprintf(stderr,"Too long word %s\n",process);
                }
                        process[i++] = k;
                        k = fgetc(f1);
                        fprintf(stderr, "Reading sym = %d\n", k);
        }
	process[i] = '\0';
	if(process[0] == ':') {
		fprintf(stderr,"WE START TO CONVERT LABLE\n");
		sscanf(&process[1],"%lf",&dval2);
        	t1[t].go = dval2;
		t1[t].addr = n;
		fprintf(stderr,"our lable %lg\n",t1[t].go);
		t++;
		fprintf(stderr,"our %d\n",n);
        } else if(!strcmp(process,"PUSH")) {
			fprintf(stderr,"WE START TO CONVERT PUSH\n");
                	t2->oper[n]  = 1;
			n++;
                	t2->oper[n] = convert_arg(f1);
			n++;
			t2->oper[n] = convert_arg(f1);
			fprintf(stderr,"We've converted arg\n");	
			n++;
                	fprintf(stderr,"we continue\n");
        } else  if (!strcmp(process,"POP")) {
			fprintf(stderr,"WE START TO CONVERT POP\n");
                        t2->oper[n] = 2;
			n++;
                        t2->oper[n] = convert_arg(f1);
			n++;
			t2->oper[n] = convert_arg(f1);
			n++;
        } else  if(!strcmp(process,"ADD")) {
                        fprintf(stderr,"WE START TO CONVERT ADD\n");
			t2->oper[n] = 3;
			n++;
        } else  if(!strcmp(process,"SUB")) {
			fprintf(stderr,"WE START TO CONVERT SUB\n");
                        t2->oper[n] = 5;
			n++;

         } else if(!strcmp(process,"JMP")) {
			fprintf(stderr,"WE START TO CONVERT JMP\n");
                        t2->oper[n] = 11;
			n++;
			t2->oper[n] = convert_arg(f1);
			n++;
			dval1 = convert_arg(f1);
			int c = 0;
                        for(m = 0;m <= t;m++){
				if(t1[m].go == dval1) {
					t2->oper[n] = t1[m].addr;
					n++;
					c = 1;
					break;
					}
			}
			if(c == 0){
				t2->oper[n] = -1;
				n++;
			}
				

        } else if(!strcmp(process,"JA")) {
			fprintf(stderr,"WE START TO CONVERT JA\n");
                        t2->oper[n] = 12;
			n++;
			t2->oper[n] = convert_arg(f1);
                        n++;
                        dval1 = convert_arg(f1);
			fprintf(stderr,"our arg of jmp %lf\n",dval1);
                        int c = 0;
                        for(m = 0;m <= t;m++){
				fprintf(stderr,"our lable %lf\n",t1[t].go);
                                if(t1[m].go == dval1) {
                                        t2->oper[n] = t1[m].addr;
                                        n++;
                                        c = 1;
                                        break;
                                        }
                        }
                        if(c == 0){
                                t2->oper[n] = -1;
                                n++;
                        }

        } else if(!strcmp(process,"JAE")) {
			fprintf(stderr,"WE START TO CONVERT JAE\n");
                        t2->oper[n] = 13;
			n++;
			t2->oper[n] = convert_arg(f1);
                        n++;
			dval1 = convert_arg(f1);
			int c = 0;
                        for(m = 0;m <= t;m++){
                                if(t1[m].go == dval1) {
                                        t2->oper[n] = t1[m].addr;
                                        n++;
                                        c = 1;
                                        break;
                                        }
                        }
                        if(c == 0){
                                t2->oper[n] = -1;
                                n++;
                        }
	} else if(!strcmp(process,"JB")){
			fprintf(stderr,"WE START TO CONVERT JB\n");
        		t2->oper[n] = 14;
			n++;
			t2->oper[n] = convert_arg(f1);
                        n++;
			dval1 = convert_arg(f1);
			int c = 0;
                        for(m = 0;m <= t;m++){
                                if(t1[m].go == dval1) {
                                        t2->oper[n] = t1[m].addr;
                                        n++;
                                        c = 1;
                                        break;
                                        }
                        }
                        if(c == 0){
                                t2->oper[n] = -1;
                                n++;
                        }

	} else if(!strcmp(process,"JBE")) {
			fprintf(stderr,"WE START TO CONVERT JBE\n");
                        t2->oper[n] = 15;
			n++;
			t2->oper[n] = convert_arg(f1);
                        n++;
			dval1 = convert_arg(f1);
			int c = 0;
                        for(m = 0;m <= t;m++){
                                if(t1[m].go == dval1) {
                                        t2->oper[n] = t1[m].addr;
                                        n++;
                                        c = 1;
                                        break;
                                        }
                        }
                        if(c == 0){
                                t2->oper[n] = -1;
                                n++;
                        }

        } else if(!strcmp(process,"JE")) {
			fprintf(stderr,"WE START TO CONVERT JE\n");
                        t2->oper[n] = 17;
			n++;
			t2->oper[n] = convert_arg(f1);
                        n++;
                        dval1 = convert_arg(f1);
			int c = 0;
                        for(m = 0;m <= t;m++){
                                if(t1[m].go == dval1) {
                                        t2->oper[n] = t1[m].addr;
                                        n++;
                                        c = 1;
                                        break;
                                        }
                        }
                        if(c == 0){
                                t2->oper[n] = -1;
                                n++;
                        }

        } else  if(!strcmp(process,"JHE")) {
			fprintf(stderr,"WE START TO CONVERT JHE\n");
			t2->oper[n] = 18;
			n++;
			t2->oper[n] = convert_arg(f1);
                        n++;
                        dval1 = convert_arg(f1);
			int c = 0;
                        for(m = 0;m <= t;m++){
                                if(t1[m].go == dval1) {
                                        t2->oper[n] = t1[m].addr;
                                        n++;
                                        c = 1;
                                        break;
                                        }
                        }
                        if(c == 0){
                                t2->oper[n] = -1;
                                n++;
                        }

        } else if(!strcmp(process,"CALL")) {
			fprintf(stderr,"WE START TO CONVERT CALL\n");
                        t2->oper[n] = 19;
			n++;
			t2->oper[n] = convert_arg(f1);
                        n++;
                        dval1 = convert_arg(f1);	
			int c = 0;
                        for(m = 0;m <= t;m++){
                                if(t1[m].go == dval1) {
                                        t2->oper[n] = t1[m].addr;
                                        n++;
                                        c = 1;
                                        break;
                                        }
                        }
                        if(c == 0){
                                t2->oper[n] = -1;
                                n++;
                        }

        } else if(!strcmp(process,"RET")) {
			fprintf(stderr,"WE START TO CONVERT RET\n");
                        t2->oper[n] = 20;
			n++;
        } else if(!strcmp(process,"MULL")) {
			fprintf(stderr,"WE START TO CONVERT MUL\n");
                        t2->oper[n] = 4;
			n++;
        } else if(!strcmp(process,"DIV")) {
			fprintf(stderr,"WE START TO CONVERT DIV\n");
                        t2->oper[n] = 6;
			n++;
        } else if(!strcmp(process,"OUT")) {
			fprintf(stderr,"WE START TO CONVERT OUT\n");
                        t2->oper[n] = 7;
			n++;
        } else  if(!strcmp(process,"IN")) {
			fprintf(stderr,"WE START TO CONVERT IN\n");
                        t2->oper[n] = 8;
			n++;
        } else if(!strcmp(process,"POPR")) {
			fprintf(stderr,"WE START TO CONVERT POPR\n");
                        t2->oper[n] = 9;
			n++;
			t2->oper[n] = convert_arg(f1);
			n++;
			t2->oper[n] = convert_arg(f1);
			n++;
        } else if(!strcmp(process,"PUSHR")) {
			fprintf(stderr,"WE START TO CONVERT PUSHR\n");
                        t2->oper[n] = 10;
			n++;
                        t2->oper[n] = convert_arg(f1);
			n++;
			t2->oper[n] = convert_arg(f1);
			n++;
			
        } else if(!strcmp(process,"NOCOMMAND")) {
			fprintf(stderr,"WE START TO CONVERT NOCOMMAND\n");
                        t2->oper[n] = 0;
			n++;
                     
        } else if(!strcmp(process,"")) {
                        fprintf(stdout,"That's all\n");
			return 0;
                        
        } else {
                fprintf(stderr,"UNKNOWN PROCESS%s\n",process);
  		return 0;    
        }
	}

}

void print_table(FILE* f2,table2* t2){
	char* name_out = "f_out.txt";
	double value;
	int n = 0;
	value = t2->oper[n];
	f2 = fopen(name_out,"w+");
	while(t2->oper[n]){
		fprintf(f2,"%lg ",value);
		fprintf(stderr,"%lg\n",value);
		value = t2->oper[++n];
	}
}

int main(int argc, char **argv) {
	table1* t1;
	table2* t2;
	FILE* f1 = NULL;
	FILE* f2 = NULL;
	char* name_in = "f_in.txt";
	char* name_out = "f_out.txt";
	int f = 1;
	f1 = fopen(name_in,"r");
	f2 = fopen(name_out,"wb+");
	t1 = (table1*)calloc(MAX_OP,sizeof(table1));
	t2 = (table2*)calloc(1,sizeof(table2));
	t2->oper = (double*)calloc(MAX_OP,sizeof(double));
	fprintf(stderr,"We start to create our table\n");
	create_table(f1,t1,t2);
	create_table(f1,t1,t2);
	fclose(f1);	
	fprintf(stderr,"We finished creating\n");
	switch(argc-1) {
		case 1:
			name_in = argv[1];
			break;
		case 2:
			name_in = argv[1];
			name_out = argv[2];
			break;
		default:
			fprintf(stderr,"Please,try to give  necessary arguments\n");
			return -1;
	}
	fprintf(stderr,"We start to print\n");
	print_table(f2,t2);
	fprintf(stderr,"that's all\n");
	fclose(f2);
	return 0;
}
