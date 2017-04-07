#include<cstdlib>
#include<cassert>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<malloc.h>


using namespace std;


#define F_MAXLINE 9
#define ARG_MAXLINE 10

#define NOCOMMAND 0
#define PUSH 1
#define POP 2
#define ADD 3
#define mul 4
#define SUB 5
#define DIV 6
#define OUT 7           
#define IN 8
#define POPR 9
#define PUSHAX 10
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

#define a_prep 'h' 

typedef struct _table {
	char* oper;
	int addr;
} table;



int convent_arg(FILE* f1,FILE* f2) {
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
                fwrite(&val,sizeof(int),1,f2);
		fprintf(stderr,"DANIK PIDOR\n");
                return 1;
                }
        if(f == 3) {
                sscanf(arg,"%lf",&dval);
		fwrite(&dval,sizeof(double),1,f2);
                return 1;
                }
        if(!strcmp(arg,"ax")) {
	        fputc(ax,f2);
  		fputc(r_code,f2);
                return 1;
                }
        if(!strcmp(arg,"bx")) {
                fputc(bx,f2);
    		fputc(r_code,f2);
                return 1;
                }
        if(!strcmp(arg,"cx")) {
                fputc(cx,f2);
              	fputc(r_code,f2);
                return 1;
                }
        if(!strcmp(arg,"dx")) {
                fputc(dx,f2);
        	fputc(r_code,f2);
                return 1;
                }
        if(arg[0] = 'h') {
                sscanf(&arg[1],"%d",&val);
            	fputc(a_code,f2);
                fwrite(&par,sizeof(int),1,f2);
                }
        if(!strcmp(arg,"")) {
                fprintf(stderr,"Please,give me some argument%s\n",arg);
                return 0;
                }
      
}

unsigned int conventer(FILE* f1,FILE* f2) {
	
	char k ;
	char* process;  
      	process = (char*)calloc(F_MAXLINE,sizeof(char));
	int i = 0;
	int val;
	k = fgetc(f1);
 	printf("We continue to work\n");	
	fprintf(stderr, "Reading sym %d\n", k);

	while (k && !isspace(k) && k!= EOF) {	
		if (i >=F_MAXLINE) {
			fprintf(stderr,"Too long word %s\n",process);
		}
			process[i++] = k;
			k = fgetc(f1);	
			fprintf(stderr, "Reading sym %d\n", k);
		
	}	
	printf("%p\n\n", f2);

	fprintf(stderr,"WE'RE STARTING TO CONVERT\n");
	fprintf(stderr,"my process %s\n",process);

	if(process[0] == ':') { 
		fputs(process,f2);
	} else 
	if(!strcmp(process,"PUSH")) {
		fputc(PUSH, f2);
		fprintf(stderr,"We try to convert\n");
		convent_arg(f1,f2);
		
		printf("we continue\n");
	} else  if (!strcmp(process,"POP")) {
			fputc(POP,f2);
			return convent_arg(f1,f2);

	} else  if(!strcmp(process,"ADD")) {
			fputc(ADD,f2);
			printf("HEllo\n");
			return 1;
		

	} else 	if(!strcmp(process,"SUB")) {
			fputc(SUB,f2);
			return 1;
	
	 } else if(!strcmp(process,"JMP")) {
                        fputc(JMP,f2);
               //         return convert_arg(f1,f2);

	
	} else if(!strcmp(process,"JA")) {
			fputc(JA,f2);
//			return convert_arg(f1,f2);
	
	} else if(!strcmp(process,"JAE")) {                                                     
                        fputc(JAE,f2);                                                          
  //                      return convert_arg(f1,f2);  
	
	} else if(!strcmp(process,"JB")) {                                                     
                        fputc(JB,f2);                                                          
    //                    return convert_arg(f1,f2);  
	
	} else if(!strcmp(process,"JBE")) {                                                     
                        fputc(JBE,f2);                                                          
      //                  return convert_arg(f1,f2);  

	} else if(!strcmp(process,"JE")) {                                                     
                        fputc(JE,f2);                                                          
        //                return convert_arg(f1,f2);  
	
	} else if(!strcmp(process,"JHE")) {  
                                               
                        fputc(JHE,f2);                                                          
          //              return convert_arg(f1,f2); 
	
	} else if(!strcmp(process,"CALL")) {                                                     
                        fputc(CALL,f2);                                                          
            //            return convert_arg(f1,f2);   	
	
	} else if(!strcmp(process,"RET")) {                                                     
                        fputc(RET,f2);                                                         
			return 1;
					
		
	} else if(!strcmp(process,"mul")) {
			fputc(mul,f2);
			return 1;
		

	} else if(!strcmp(process,"DIV")) {
			fputc(DIV,f2);
			return 1;
	
		
	} else if(!strcmp(process,"OUT")) {
			fputc(OUT,f2);
			return 1;
		

	} else 	if(!strcmp(process,"IN")) {
			fputc(IN,f2);
			return 1;
		

	} else if(!strcmp(process,"POPAX")) {
			fputc(POPAX,f2);
			return convent_arg(f1,f2);
		

	} else if(!strcmp(process,"PUSHAX")) {
			fputc(PUSHAX,f2);
			return convent_arg(f1,f2);
		
	
        } else if(!strcmp(process,"NOCOMMAND")) {
                        fputc(NOCOMMAND,f2);
                        return 1;

		
	} else if(!strcmp(process,"")) {
			fprintf(stdout,"That's all\n");
			return 0;
			}
	else {
		fprintf(stderr,"UNKNOWN PROCESS%s\n",process);
		return 0;
	}
		

}						

/*void table_create(FILE* f_in,FILE* f_out,table* t) {
	t = (table*)malloc(sizeof(table)*50);
	char value;
*/	

int main(int argc, char **argv) {
	FILE* f1 = NULL;
		
	FILE* f2 = NULL;
	
	char* name_in;
	char* name_out;
	int f = 1;
	name_in = "f_in.txt";
	name_out = "f_out.txt";
	
	switch(argc-1) {
		case 1:
			name_in = argv[1];
			break;
		case 2:
			name_in = argv[1] ;
			name_out = argv[2] ;	
			break;
		default:	
			fprintf(stderr,"We have some problems,captain\n");
			return 1;
			
	}
	
	f1 = fopen(name_in,"r");
	f2 = fopen(name_out,"w+");	
	printf("%p\n%s\n", f2, name_out);

	
	printf("%d\n",f);
	
	while(f){
		printf("all ok\n");		
		f = conventer(f1, f2);
		
	}
	
	fclose(f1);
	fclose(f2);
	return 0;
}

