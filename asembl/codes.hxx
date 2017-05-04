#ifndef _CODES_H_
#define _CODES_H_

#include<cstdio>                                                                                
#include<cstdlib>                                                                               
#include<cassert>                                                                               
#include<iostream>                                                                              
#include"stack.hxx"                                                                             

#define F_MAXLINE 6                                                                             
#define ARG_MAXLINE 10                                                                          
#define RAM_SIZE 256                                                                            
#define MAX_OP 256                                                                              
#define STACK_SIZE 128                                                                          
#define EXIT  0                                                                                 
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
#define JA_NEW 21                                                                               
#define JAE_NEW 22                                                                              
#define JB_NEW 23                                                                               
#define JBE_NEW 24                                                                              
#define JE_NEW 25                                                                               
#define JHE_NEW 26                                                                              

#define R_eax 21
#define R_ebx 22                                                                                
#define R_ecx 23
#define R_edx 24                                                                                
#define R_eip 25
#define R_ebp 26                                                                                
#define R_esp 27

#define r_code 1                                                                                                
#define a_code 2
#define num_i   3
#define num_d   4
#define ra_code 5
#define in_tr 6
#define a_prep 'h' 


#endif /*_CODES_H_*/
