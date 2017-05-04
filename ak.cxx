#include<iostream>
#include"akinator.hxx"
#include <cstring>
#include <cassert>
#define MAX_SYM 100
#define MAX_PREP 15

using namespace std;

Node :: Node(char* data,Node* no,Node* yes):
	question(data),
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
	fprintf(stderr,"%s\n",root->question);
}	

void Node :: print_tree(FILE* f_out,Node* root) {
	if(root != NULL) {
		fprintf(f_out,"(%s",root->question);
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

void Node :: akinator(Node* root) {
	char* answer;
	char* data;
	int len_d = 0;
	int len_a = 0;
	look(root);
	data = (char*)calloc(MAX_SYM,sizeof(char));
	answer = (char*)calloc(MAX_PREP,sizeof(char));
	fscanf(stdin,"%s",answer);
	if(strcmp(answer,"да") && strcmp(answer,"нет")) {
		fprintf(stderr,"Используйте только да или нет\n");
		akinator(root);
	}
	if(!strcmp(answer,"нет")){
		if(root->left != NULL) {
			akinator(root->left);
		} else {
			fprintf(stderr,"Кто это?\n");
                        fscanf(stdin,"%s",answer);
			len_a = strlen(answer);
                        fprintf(stderr,"Чем  %s отличается от %s\n",answer,root->question);
                        getc(stdin);
                        fgets(data,MAX_SYM,stdin);
                        len_d = strlen(data);
                        data[len_d-1] = '?';
			answer[len_a] = '?';
                        root->left = new Node(root->question,NULL,NULL);
                        root->right = new Node(answer,NULL,NULL);
                        root->question = data;
			return;
		 	}	
	} 
	if(!strcmp(answer,"да")) {
		if(root->right != NULL) {
			akinator(root->right);
		} else {
			fprintf(stderr,"Спасибо за игру\n");
		}	
	
	} 
}	

int main(int argc,char** argv) {
        FILE* f_in = fopen("tree_save.txt","r");	
	char*name_in = "tree_save.txt";
        switch(argc-1) {
                case 1 :
                name_in  = argv[1];
                break;
                default:
                fprintf(stderr,"Few args\n");
                break;
}
	Node* node = node->create_tree(f_in);
	node->akinator(node);
	f_in = fopen("tree_save.txt","w");
	node->print_tree(f_in,node);
        return 0;
}

