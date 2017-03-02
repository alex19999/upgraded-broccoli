#include<cstdlib>
#include<cassert>
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

#define F_MAXLINE 6
#define ARG_MAXLINE 10

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

#define ax 0x01
#define bx 0x02
#define cx 0x03
#define dx 0x04

#define reg_code 0x01
#define add_code 0x02
#define adres_prepositon 'h' 

/*
	prog := statement+
	statement := op x y z
*/
int convent_arg(FILE* f1,FILE* f2) {
        char par;
        char* arg;
        arg = (char*)calloc(ARG_MAXLINE,sizeof(char));
	int i = 0;
        int f = 0;
        par = fgetc(f1);
        int val;
	
        double dval;
	
        while(par && !isspace(par)) {
        if(i >= ARG_MAXLINE) {
                fprintf(stderr,"TOO LONG ARGUMENT%s\n",arg);
                return 0;
        } else {
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
                return 1;
                }
        if(f == 3) {
                sscanf(arg,"%lf",&dval);
                fwrite(&dval,sizeof(double),1,f2);
                return 1;
                }
        if(!strcmp(arg,"ax")) {
	        fwrite(arg,sizeof(char),2,f2);
               // fwrite("reg_code",sizeof(char),7,f2);
                return 1;
                }
        if(!strcmp(arg,"bx")) {
                fwrite(arg,sizeof(char),2,f2);
               // fwrite("reg_code",sizeof(char),7,f2);
                return 1;
                }
        if(!strcmp(arg,"cx")) {
                fwrite(arg,sizeof(char),2,f2);
               // fwrite("reg_code",sizeof(char),7,f2);
                return 1;
                }
        if(!strcmp(arg,"dx")) {
                fwrite(arg,sizeof(char),2,f2);
               // fwrite("reg_code",sizeof(char),8,f2);
                return 1;
                }
        if(arg[0] = 'h') {
                sscanf(&arg[1],"%d",&val);
              //  fwrite("add_code",sizeof(char),8,f2);
                fwrite(&par,sizeof(int),1,f2);
                }
        if(!strcmp(arg,"")) {
                fprintf(stderr,"Please,give me adress%s\n",arg);
                return 0;
                }
        }
}

unsigned int conventer(FILE* f1,FILE* f2) {
	char k;
	char* s;                                               //our function//
	s = (char*)calloc(F_MAXLINE,sizeof(char));
	f1 = fopen("text1.txt","r");
	f2 = fopen("text2.txt","wb");
	k = fgetc(f1);
	int i = 0;
	while (s != " " && s != "\n" && s != "\t") {	
		if (i >=F_MAXLINE) {
			fprintf(stderr,"Too long word %s\n",s);
		} else {
			s[i++] = k;
			k = fgetc(f1);
		}
	
	
		if(!strcmp(s,"PUSH")) {
			fwrite(s,sizeof(char),4,f2);
			return convent_arg(f1,f2);
			
	        } else  if (!strcmp(s,"POP")) {
				fwrite(s,sizeof(char),3,f2);
                		return convent_arg(f1,f2);

		} else  if(!strcmp(s,"ADD")) {
				fwrite(s,sizeof(char),3,f2);
                		return 1;
			

		} else 	if(!strcmp(s,"SUB")) {
				fwrite(s,sizeof(char),3,f2);
                		return 1;
						
			
		} else if(!strcmp(s,"MUL")) {
				fwrite(s,sizeof(char),3,f2);
                		return 1;
			

 		} else if(!strcmp(s,"DIV")) {
				fwrite(s,sizeof(char),3,f2);
                		return 1;
		
			
		} else if(!strcmp(s,"OUT")) {
				fwrite(s,sizeof(char),3,f2);
                		return 1;
			

  		} else 	if(!strcmp(s,"IN")) {
				fwrite(s,sizeof(char),2,f2);
                		return 1;
			

		} else if(!strcmp(s,"POPAX")) {
				fwrite(s,sizeof(char),5,f2);
                		return convent_arg(f1,f2);
			

		} else if(!strcmp(s,"PUSHAX")) {
                        	fwrite(s,sizeof(char),6,f2);
                        	return convent_arg(f1,f2);
			

			
		} else if(!strcmp(s,"")) {
				fprintf(stdout,"That's all\n");
				return 0;
				}
		
			
		}

}						

int main(int argc, char **argv) {
	FILE* f1;
	FILE* f2;
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
	f2 = fopen(name_out,"wb+");
	while(f){
		f = conventer(f1, f2);
	}
	return 0;
}

