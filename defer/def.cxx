#include<iostream>
#include"def.hxx"
#include <cstring>
#include <cassert>
#define MAX_SYM 100
#define MAX_OP 6

using namespace std;

Node :: Node(const char* data,Node* no,Node* yes):
        oper(data),
        left(no),
        right(yes)
{}



Node* Node :: create_tree(FILE* f_in) {
        char* data;
        int i = 0;
        char sym = 0;
        data = (char*)calloc(MAX_SYM,sizeof(char));
        sym = fgetc(f_in);
        assert(sym == '(');
        fscanf(f_in,"%[^()]",data);
        if(!strcmp(data, "n")){
                assert(fgetc(f_in) == ')');
                return NULL;
        }
        Node* root = new Node(data,NULL,NULL);
        root->left = create_tree(f_in);
        root->right = create_tree(f_in);
        assert(fgetc(f_in) == ')');
        return root;
        }

void Node :: look(Node* root) {
        fprintf(stderr,"%s\n",root->oper);
}

const char*  Node :: ret(Node* root){
	return root->oper;
}

int Node ::  determ(Node* root){
	const char* s ;
	s = (char*)calloc(MAX_OP,sizeof(char));
	s = root->oper;
	fprintf(stderr,"our root = %s\n",root->oper);
	fprintf(stderr,"our s = %s\n",s);
	if(!strcmp(s,"+")) return 1;
	if(!strcmp(s,"-")) return 2;
	if(!strcmp(s,"/")) return 3;
	if(!strcmp(s,"*")) return 4;
	if(!strcmp(s,"ln")) return 5;
	if(!strcmp(s,"cos")) return 6;
	if(!strcmp(s,"sin")) return 7;
	if(!strcmp(s,"^")) return 8;
	if(!strcmp(s,"log")) return 9;
	if(!strcmp(s,"x")) return 0;
	else return -1;
}

	

void Node :: print_tree(FILE* f_out,Node* root) {
        if(root != NULL) {
                fprintf(f_out,"(%s",root->oper);
                }
        if(root->left != NULL) {
                print_tree(f_out,root->left);
        } else {
                fprintf(f_out,"(n)");
                }
        if(root->right != NULL) {
                print_tree(f_out,root->right);
        } else {
                fprintf(f_out,"(n)");
        }
        fprintf(f_out,")");
        return ;
}

Node* Node :: def(Node* root) {
	int num;
	fprintf(stderr,"we are here\n");
	Node* l_left;
	Node* r_left;
	Node* l_right;
	Node* r_right;
	num = determ(root);
	Node* newroot = new Node(oper,NULL,NULL);
	fprintf(stderr,"num = %d\n",num);
	switch(num) {
		case -1:
		newroot->oper = "0";
		break;
		case 0:
		newroot->oper = "1";
		break;
		case 1:
		newroot->oper = "+";
		newroot->left = def(root->left);
		newroot->right = def(root->right);
		break;
		case 2:
		newroot->oper = "-";
		newroot->left = def(root->left);
		newroot->right = def(root->right);
		break;
		case 3:
		newroot->oper = "/";
		l_left = new Node("*",def(root->left),root->right);
		l_right = new Node("*",root->left,def(root->right));
		newroot->left = new Node("-",l_left,l_right);
		newroot->right = new Node("*",root->right,root->right);
		break;
		case 4:
		newroot->oper = "+";
		newroot->left = new Node("*",def(root->left),root->right);
		newroot->right = new Node("*",root->left,def(root->right));	
		break; 
		case 5 :
		newroot->oper = "*";
		l_left = new Node("1",NULL,NULL);
		newroot->left = new Node("/",l_left,root->left);
		newroot->right = def(root->left);
		break;
	        case 6:
		newroot->oper = "*";
		newroot->left = new Node("-sin",root->left,NULL);
		newroot->right = def(root->left);
		break;
		case 7:
		newroot->oper = "*";
		newroot->left = new Node("cos",root->left,NULL);
                newroot->right = def(root->left);
                break;
		case 8:
		if(determ(root->left) != -1) {
			if(root->right != 0) {
				newroot->oper = "*";
				l_right = new Node("1",NULL,NULL);
				r_right = new Node("-",root->right,l_right);
				newroot->left = new Node("^",root->left,r_right);
			} else {
				newroot = l_right;
			}
		} else {
			if (determ(root->right) != -1) {
				newroot->oper = "*";
				newroot->left = root;
				newroot->right = new Node("ln",root->left,NULL);
			} else newroot = new Node("0",NULL,NULL);
				
		}
		case 9:
		if (determ(root->right) == -1) {
			newroot->oper = "*";
			r_left = new Node("1",NULL,NULL);
			r_right = new Node("ln",root->right,NULL);
			l_left = new Node("*",root->left,r_right);
			newroot->left = new Node("/",r_left,l_left);
			newroot->right = def(root->left);
			}
		break;	 
		default:
		fprintf(stderr,"thats all\n");
		break;
	}
	return newroot;
}
		
		
				
	


int main(int argc,char** argv) {
        FILE* f_in = fopen("tree_cr.txt","r");
	FILE* f_out = fopen("tree_s.txt","w+");
        const char* name_in = "tree_cr.txt";
	const char* name_out = "tree_s.txt";
        switch(argc-1) {
                case 1 :
                name_in  = argv[1];
                break;
		case 2 :
		name_in = argv[1];
		name_out = argv[2];
		break;
                default:
                fprintf(stderr,"Few args\n");
                break;
}
	Node* node = node->create_tree(f_in);
	Node* node1 = node->def(node);
        node->print_tree(f_out,node1);
        return 0;
}

