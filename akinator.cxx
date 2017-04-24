#include<cstdlib>
#include<cstdio>
#include<iostream>
#include"akinator.hxx"

#define MAX_SYM 100
#define MAX_PREP 15

using namespace std;

Node :: Node(char* question,Node* left,Node* right) :
	question(data),
	left(),
	right()
{}

Tree :: Tree() {	
	}

void Tree :: create_tree(FILE* f_in) {
	f_in = fopen("tree_cr.txt","r");
	fprintf(stderr,"here\n");
	char* que = (char*)calloc(MAX_SYM,sizeof(char));
	char* var_one = (char*)calloc(MAX_PREP,sizeof(char));
	char* var_two = (char*)calloc(MAX_PREP,sizeof(char));
	int i = 0;
	int k = 0;
	int m = 0;
 	char sym = 0;
	if(f_in != NULL) {
	sym = fgetc(f_in);
	fprintf(stderr,"we started to read\n");
	if(sym == '(') {
		sym = fgetc(f_in);
		while(sym && sym != EOF && sym != '(') {
		fprintf(stderr,"our symball = %c\n",sym);
		que[i++] = sym;
		sym = fgetc(f_in);
      		}
		sym = fgetc(f_in);
		while(sym && sym != EOF && sym != '(' && sym != ')') {
		var_one[m++] = sym;
		fprintf(stderr,"our sym = %c\n",sym);
                sym = fgetc(f_in);
		}
		sym = fgetc(f_in);
		sym = fgetc(f_in);
		fprintf(stderr,"cur = %c\n",sym);
		while(sym && sym != EOF && sym != ')') {
                var_two[k++] = sym;
		fprintf(stderr,"our sym = %c\n",sym);
                sym = fgetc(f_in);
		}
	}
}
	fprintf(stderr,"our que = %s\n",que);
	fprintf(stderr,"our var_one = %s\n",var_one);
	fprintf(stderr,"our var_two = %s\n",var_two);
	Node* no = new Node(var_one,NULL,NULL);
	Node* yes = new Node(var_two,NULL,NULL);
	Node* cur = new Node(que,no,yes);
	fprintf(stderr,"out = %s\n",no->data);
	
}

int main(int argc,char** argv) {
	FILE* f_in;
        char* name_in = "tree_cr.txt";
        fopen(name_in,"r");
	switch(argc-1) {
		case 1 :
		name_in = argv[1];
		break;
		default:
		fprintf(stderr,"хуй\n");
		break;
}
	fprintf(stderr,"ok\n");
	Tree* tree1 = new Tree();
	fprintf(stderr,"ok1\n");
	tree1->create_tree(f_in);
	fprintf(stderr,"ok3\n");
	return 0;
}
